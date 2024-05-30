#include <Arduino.h>

//External Sensors
#include "TempSensor.h"
#include "TurbiditySensor.h"
#include "SalinitySensor.h"

extern "C"  {
    //Internal ESP peripherals
    #include <esp_sleep.h>
    void app_main();
}

extern "C" void app_main() {

    //Variables
    float temperature;
    //float humidity;
    float turbidity;

    //Initializations
    temp.begin();
    tbdty.begin();

    while(1)    {
        
        temp.readTemperature(FAHRENHEIT, &temperature);
        temperature = round(temperature * 1000.0) / 1000.0;

        tbdty.begin();
        turbidity = tbdty.readTurbidity(&turbidity);
        delay(1000);
    }

}


