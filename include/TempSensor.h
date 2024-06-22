#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H
#include <DHT2.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#define DHTPIN (gpio_num_t) 0
enum TEMP {CELSIUS,FAHRENHEIT};


class TempSensor
{
public:
    static constexpr uint8_t ONE_WIRE_BUS = 33;
    //static constexpr uint8_t DHTPIN = 5;
    //static constexpr uint8_t DHTTYPE = DHT22;
    static constexpr uint8_t TEMP_INDEX = 0;

    static TempSensor& Get();
    void begin();
    bool readTemperature(TEMP tempScale, float* temperature);
    bool readHumidity(float* humidity);

private:
    TempSensor();
    DHT2 dht;   //new dht code for esp
    OneWire oneWire;
    DallasTemperature sensors;
    
    //making it signletton
    TempSensor (const TempSensor&) = delete;
    TempSensor& operator=(const TempSensor&)=delete; 

};

extern TempSensor& temp;

#endif