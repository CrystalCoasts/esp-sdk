#ifndef BLE_H
#define BLE_H

#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_gatt_defs.h"
#include "esp_gatt_common_api.h"
#include <vector>

enum BLE_STATUS {IDLE, TRANSMITING, RECEIVING};
enum SENSORS {TEMP, SALINITY, TURBIDITY, PH, DO};
class BLE {
private:
    static BLE* instance;

    BLE(); // Private constructor
    ~BLE(); // Private destructor

    BLE(const BLE&) = delete; // Delete copy constructor
    BLE& operator=(const BLE&) = delete; // Delete copy assignment operator

    static constexpr uint16_t SENSOR_SERVICE_UUID = 0x0A;
    static constexpr uint16_t SYSTEM_SERVICE_UUID = 0x0B;

    static constexpr uint16_t SENSOR_START_UUID = 0xA0;
    static constexpr uint16_t SENSOR_STOP_UUID = 0xA1;
    static constexpr uint16_t SENSOR_READ_UUID = 0xA2;
    static constexpr uint16_t SENSOR_CALIBRATE_UUID = 0xA3;
    static constexpr uint16_t SENSOR_ALERT_UUID = 0xA4;

    static constexpr uint16_t SYSTEM_BATTERY_UUID = 0xB0;
    static constexpr uint16_t SYSTEM_UPDATE_UUID = 0xB1;
    static constexpr uint16_t SYSTEM_REFRESH_UUID = 0xB2;
    static constexpr uint16_t SYSTEM_RESET_UUID = 0xB3;

    struct BLECharacteristic {
        esp_bt_uuid_t uuid;
        esp_gatt_char_prop_t properties;
        uint16_t handle;
    };

    struct BLEService {
        esp_gatt_srvc_id_t service_id;
        uint16_t service_handle;
        std::vector<BLECharacteristic> characteristics;
    };

    BLEService sensor_service;
    BLEService system_service;

    static constexpr const char* GATTS_TABLE_TAG = "GATTS_TABLE";

    void initServices();
    void addCharacteristics(BLEService& service, esp_gatt_if_t gatts_if);
    void createServices(esp_gatt_if_t gatt_if);

public:
    static BLE* getInstance();

    void startAdvertising();
    void stopAdvertising();
    void handleStartCharacteristic(SENSORS sensor);
    void handleData(uint8_t* data, size_t len);
    void gattsEventHandler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param);
};

#endif // BLE_H
