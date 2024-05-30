#include <Arduino.h>

//External Sensors
#include "TempSensor.h"
#include "TurbiditySensor.h"
#include "SalinitySensor.h"

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

#define SSID = "seawall"
#define PASSWD = "12345678"
#define WEB_APP_URL = "https://script.google.com/macros/s/AKfycbzdREDYLRb1ew8CjwGY_WnrIU0UWW0Sn3Wr4XdT8Jv0VjXuQxJV7GVCKZeYtEb2zrKb/exec"

#define STATUS_LED_PIN GPIO_NUM_2 // Commonly the onboard LED pin on ESP32
#define BUTTON_PIN GPIO_NUM_0   

//forward declartions

void gpio_init();

extern "C"  {
    //Internal ESP peripherals
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
    //float humidity;
    float turbidity;

    //Initializations
    gpio_init();

    temp.begin();
    tbdty.begin();


    while(1)    {
        
        temp.readTemperature(FAHRENHEIT, &temperature);
        temperature = round(temperature * 1000.0) / 1000.0;

        tbdty.begin();
        turbidity = tbdty.readTurbidity(&turbidity);
        delay(1000);
        printf("Temperature: %f, Turbidity: %f", temperature, turbidity);
    }

}

void gpio_init() {
    gpio_set_direction(STATUS_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
}



