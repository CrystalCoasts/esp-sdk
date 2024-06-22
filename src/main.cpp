#include <Arduino.h>
#include <Wire.h>

//External Sensors
#include "TempSensor.h"
#include "TurbiditySensor.h"
#include "SalinitySensor.h"

#include "ble.h"

//Internal ESP peripherals
#include <esp_sleep.h>
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_http_client.h"
#include "esp_spiffs.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "SPIFFS.h"
#include "driver/adc.h"
#include "cJSON.h"

//Definitions and Constants
#define WIFI_SSID "seawall"
#define WIFI_PASS "12345678"
#define WEB_APP_URL "https://script.google.com/macros/s/AKfycbzdREDYLRb1ew8CjwGY_WnrIU0UWW0Sn3Wr4XdT8Jv0VjXuQxJV7GVCKZeYtEb2zrKb/exec"
#define STATUS_LED_PIN GPIO_NUM_2 // Commonly the onboard LED pin on ESP32
#define BUTTON_PIN GPIO_NUM_0   
#define SDA_PIN 21
#define SCL_PIN 22

//Sensor Data Struct
struct SensorData {
    float humidity;
    bool humidityValid;
    float temperature;
    bool temperatureValid;
    float turbidity;
    bool turbidityValid;
    float salinity;
    bool salinityValid;
    float tds;
    bool tdsValid;
    float pH;
    bool pHValid;
    float oxygenLevel;
    bool oxygenLevelValid;
};

//External C Program
extern "C"  {
    void app_main();
}

//forward declartions
void gpio_init();
void spiffs_init();
void saveDataToJSONFile(const char* data);
void uploadData(const char* data);
char* prepareJsonPayload(const SensorData* data);
void validateSensorReadings(SensorData* data);
void printDataOnCLI(const SensorData* data);
static void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
void wifi_init();

// Status functions
void blinkLED(int delayTime);
void setLEDSolid(bool on);


extern "C" void app_main() {

    //Init NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }
    
    //Variables
    // float temperature;
    // float humidity;
    // float turbidity;
    // float salinity;

    //Initializations
    wifi_init();
    gpio_init();
    spiffs_init();
    Wire.begin(SDA_PIN, SCL_PIN);
    Serial.begin(115200);

    temp.begin();
    tbdty.begin();
    tbdty.calibrate();
    sal.begin();
    sal.EnableDisableSingleReading(SAL, 1);


    while(1)    {
        
        //Sensor Data
        SensorData data = {};
        temp.readTemperature(FAHRENHEIT, &data.temperature);      
        sal.readSalinity(&data.salinity);
        tbdty.readTurbidity(&data.turbidity);
        //temp.readHumidity(&humidity);

        data.temperature = round(data.temperature * 1000.0) / 1000.0;
        data.salinity = round(data.salinity*1000)/1000;
        //turbidity = round(turbidity * 1000) / 1000;
        data.humidity = round(data.humidity * 1000) / 1000;

        // Default values for other sensors
        data.tds = 111.0;
        data.tdsValid = true;
        data.pH = 7.0;
        data.pHValid = true;
        data.oxygenLevel = 36.0;
        data.oxygenLevelValid = true;

        // Validate readings
        validateSensorReadings(&data);
        printDataOnCLI(&data);

        char* jsonPayload = prepareJsonPayload(&data);
        printDataOnCLI(&data);

        if (esp_wifi_sta_get_ap_info(NULL) == ESP_OK) {
            uploadData(jsonPayload);
        } else {
            saveDataToJSONFile(jsonPayload);
        }

        free(jsonPayload);

        // Handle button press for turbidity sensor calibration
        if (gpio_get_level(BUTTON_PIN) == 0) {
            tbdty.calibrate();
            // Simple debounce
            while (gpio_get_level(BUTTON_PIN) == 0) {
                vTaskDelay(pdMS_TO_TICKS(50));
            }
        }

        // Update LED status based on WiFi connection
        if (esp_wifi_sta_get_ap_info(NULL) == ESP_OK) {
            setLEDSolid(true);
        } else {
            blinkLED(500);
        }

        vTaskDelay(pdMS_TO_TICKS(5000)); // 5 seconds delay for next sensor read
    }
}


void gpio_init() {
    gpio_set_direction(STATUS_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
}

void spiffs_init() {
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = true
    };
    esp_vfs_spiffs_register(&conf);
}

// WiFi event handler
static void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        esp_wifi_connect();
        ESP_LOGI("WiFi", "Retrying connection...");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI("WiFi", "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
    }
}

//Initialize Wifi
void wifi_init() {
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, &instance_any_id);
    esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, &instance_got_ip);

    wifi_config_t wifi_config = {};
    strcpy((char*)wifi_config.sta.ssid, WIFI_SSID);
    strcpy((char*)wifi_config.sta.password, WIFI_PASS);
    wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;

    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    esp_wifi_start();
}

void printDataOnCLI(const SensorData* data){
    Serial.println("+-----------------------+-----------------------+");
    Serial.printf("| Temperature: %.3f\n", data->temperature);
    Serial.printf("| Salinity: %.3f\n", data->salinity);
    Serial.printf("| Turbidity: %.3f\n", data->turbidity);
    Serial.printf("| Humidity: %.3f\n", data->humidity);
    Serial.printf("| TDS: %.3f\n", data->tds);
    Serial.printf("| pH: %.3f\n", data->pH);
    Serial.printf("| Oxygen Level: %.3f\n", data->oxygenLevel);
    Serial.println("+-----------------------+-----------------------+");
}

char* prepareJsonPayload(const SensorData* data) {
    // Use cJSON instead of ArduinoJson
    cJSON *root = cJSON_CreateObject();
    if (data->humidityValid) cJSON_AddNumberToObject(root, "humidity", data->humidity);
    if (data->temperatureValid) cJSON_AddNumberToObject(root, "temperature", data->temperature);
    if (data->turbidityValid) cJSON_AddNumberToObject(root, "turbidity", data->turbidity);
    if (data->salinityValid) cJSON_AddNumberToObject(root, "salinity", data->salinity);
    if (data->tdsValid) cJSON_AddNumberToObject(root, "TDS", data->tds);
    if (data->pHValid) cJSON_AddNumberToObject(root, "pH", data->pH);
    if (data->oxygenLevelValid) cJSON_AddNumberToObject(root, "oxygenLevel", data->oxygenLevel);

    char *jsonPayload = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return jsonPayload;
}

void saveDataToJSONFile(const char* data) {
    // Similar to the original code but using ESP-IDF file functions
    FILE* f = fopen("/spiffs/data.json", "a");
    if (f == NULL) {
        ESP_LOGE("SPIFFS", "Failed to open file for writing");
        return;
    }
    fprintf(f, "%s\n", data);
    fclose(f);
}

void uploadData(const char* jsonData) {
    // Initialize all members of esp_http_client_config_t to avoid warnings
    esp_http_client_config_t config = {
        .url = "http://example.com/upload",
        .host = NULL,
        .port = 0,
        .username = NULL,
        .password = NULL,
        .auth_type = HTTP_AUTH_TYPE_NONE,
        .path = NULL,
        .query = NULL,
        .cert_pem = NULL,
        .cert_len = 0,
        .client_cert_pem = NULL,
        .client_cert_len = 0,
        .client_key_pem = NULL,
        .client_key_len = 0,
        .client_key_password = NULL,
        .client_key_password_len = 0,
        .user_agent = NULL,
        .disable_auto_redirect = false,
        .max_redirection_count = 0,
        .max_authorization_retries = 0,
        .event_handler = NULL,
        .transport_type = HTTP_TRANSPORT_OVER_TCP,
        .buffer_size = 0,
        .buffer_size_tx = 0,
        .user_data = NULL,
        .is_async = false,
        .use_global_ca_store = false,
        .skip_cert_common_name_check = false,
        .crt_bundle_attach = NULL,
        .keep_alive_enable = false,
        .keep_alive_idle = 0,
        .keep_alive_interval = 0,
        .keep_alive_count = 0,
        .if_name = NULL
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_post_field(client, jsonData, strlen(jsonData));

    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI("HTTP", "HTTP POST Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE("HTTP", "HTTP POST request failed: %s", esp_err_to_name(err));
    }

    esp_http_client_cleanup(client);
}

void validateSensorReadings(SensorData* data) {
    data->humidityValid = !isnan(data->humidity) && data->humidity >= 0 && data->humidity <= 100;
    data->temperatureValid = !isnan(data->temperature) && data->temperature >= -40 && data->temperature <= 85;
    data->turbidityValid = !isnan(data->turbidity) && data->turbidity >= 0;
    data->salinityValid = !isnan(data->salinity) && data->salinity >= 0;
    data->tdsValid = !isnan(data->tds) && data->tds >= 0;
    data->pHValid = !isnan(data->pH) && data->pH >= 0;
    data->oxygenLevelValid = !isnan(data->oxygenLevel) && data->oxygenLevel >= 0;
}

void blinkLED(int delayTime) {
    gpio_set_level(STATUS_LED_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(delayTime));
    gpio_set_level(STATUS_LED_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(delayTime));
}

void setLEDSolid(bool on) {
    gpio_set_level(STATUS_LED_PIN, on ? 1 : 0);
}


