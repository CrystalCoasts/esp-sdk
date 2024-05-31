#include <Arduino.h>
#include <Wire.h>

//External Sensors
#include "TempSensor.h"
#include "TurbiditySensor.h"
#include "SalinitySensor.h"

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
#include "driver\adc.h"


#define SSID = "seawall"
#define PASSWD = "12345678"
#define WEB_APP_URL = "https://script.google.com/macros/s/AKfycbzdREDYLRb1ew8CjwGY_WnrIU0UWW0Sn3Wr4XdT8Jv0VjXuQxJV7GVCKZeYtEb2zrKb/exec"

#define STATUS_LED_PIN GPIO_NUM_2 // Commonly the onboard LED pin on ESP32
#define BUTTON_PIN GPIO_NUM_0   

#define SDA_PIN 21
#define SCL_PIN 22

//forward declartions

void gpio_init();
void spiffs_init();

extern "C"  {
    void app_main();
}

extern "C" void app_main() {

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }
    
    //Variables
    float temperature;
    float humidity;
    float turbidity;
    float salinity;

    //Initializations
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
        
        temp.readTemperature(FAHRENHEIT, &temperature);      
        sal.readSalinity(&salinity);
        tbdty.readTurbidity(&turbidity);
        //temp.readHumidity(&humidity);

        temperature = round(temperature * 1000.0) / 1000.0;
        salinity = round(salinity*1000)/1000;
        //turbidity = round(turbidity * 1000) / 1000;
        humidity = round(humidity * 1000) / 1000;

        Serial.printf("Temp: %f, Turbidity: %f, Sal: %f\n", temperature, turbidity, salinity);  
        delay(1000);
        
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



