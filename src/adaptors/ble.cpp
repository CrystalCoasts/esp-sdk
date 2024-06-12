#include "ble.h"

BLE* BLE::instance = nullptr;

// Private constructor
BLE::BLE() {
    initServices();
}

// Private destructor
BLE::~BLE() {
    // Cleanup if necessary
}

// Get the single instance of the class
BLE* BLE::getInstance() {
    if (instance == nullptr) {
        instance = new BLE();
    }
    return instance;
}

// Initialize Services
void BLE::initServices() {
    sensor_service.service_id.is_primary = true;
    sensor_service.service_id.id.inst_id = 0x00;
    sensor_service.service_id.id.uuid.len = ESP_UUID_LEN_16;
    sensor_service.service_id.id.uuid.uuid.uuid16 = SENSOR_SERVICE_UUID;

    // Add characteristics for sensor service
    sensor_service.characteristics.push_back({ {ESP_UUID_LEN_16, {.uuid16 = SENSOR_START_UUID}}, ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE, 0 });
    sensor_service.characteristics.push_back({ {ESP_UUID_LEN_16, {.uuid16 = SENSOR_STOP_UUID}}, ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE, 0 });
    sensor_service.characteristics.push_back({ {ESP_UUID_LEN_16, {.uuid16 = SENSOR_READ_UUID}}, ESP_GATT_CHAR_PROP_BIT_READ, 0 });
    sensor_service.characteristics.push_back({ {ESP_UUID_LEN_16, {.uuid16 = SENSOR_CALIBRATE_UUID}}, ESP_GATT_CHAR_PROP_BIT_WRITE, 0 });
    sensor_service.characteristics.push_back({ {ESP_UUID_LEN_16, {.uuid16 = SENSOR_ALERT_UUID}}, ESP_GATT_CHAR_PROP_BIT_NOTIFY, 0 });

    system_service.service_id.is_primary = true;
    system_service.service_id.id.inst_id = 0x00;
    system_service.service_id.id.uuid.len = ESP_UUID_LEN_16;
    system_service.service_id.id.uuid.uuid.uuid16 = SYSTEM_SERVICE_UUID;

    // Add characteristics for system service
    system_service.characteristics.push_back({ {ESP_UUID_LEN_16, {.uuid16 = SYSTEM_BATTERY_UUID}}, ESP_GATT_CHAR_PROP_BIT_READ, 0 });
    system_service.characteristics.push_back({ {ESP_UUID_LEN_16, {.uuid16 = SYSTEM_UPDATE_UUID}}, ESP_GATT_CHAR_PROP_BIT_WRITE, 0 });
    system_service.characteristics.push_back({ {ESP_UUID_LEN_16, {.uuid16 = SYSTEM_REFRESH_UUID}}, ESP_GATT_CHAR_PROP_BIT_WRITE, 0 });
    system_service.characteristics.push_back({ {ESP_UUID_LEN_16, {.uuid16 = SYSTEM_RESET_UUID}}, ESP_GATT_CHAR_PROP_BIT_WRITE, 0 });
}

// Add Characteristics to a Service
void BLE::addCharacteristics(BLEService& service, esp_gatt_if_t gatts_if) {
    for (auto& characteristic : service.characteristics) {
        esp_ble_gatts_add_char(
            service.service_handle,
            &characteristic.uuid,
            ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
            characteristic.properties,
            NULL,
            NULL
        );
    }
}

// Create Services
void BLE::createServices(esp_gatt_if_t gatts_if) {
    // Create sensor service
    esp_ble_gatts_create_service(gatts_if, &sensor_service.service_id, 6);
    addCharacteristics(sensor_service, gatts_if);

    // Create system service
    esp_ble_gatts_create_service(gatts_if, &system_service.service_id, 6);
    addCharacteristics(system_service, gatts_if);
}

// Start Advertising
void BLE::startAdvertising() {
    // Implement advertising start logic here
}

// Stop Advertising
void BLE::stopAdvertising() {
    // Implement advertising stop logic here
}

// Handle Start Characteristic
void BLE::handleStartCharacteristic(SENSORS sensor) {
    // Implement sensor start logic here
}

// Handle Data
void BLE::handleData(uint8_t* data, size_t len) {
    if (len == sizeof(SENSORS)) {
        SENSORS sensor = static_cast<SENSORS>(*data);
        handleStartCharacteristic(sensor);
    }
}

// GATT Event Handler
void BLE::gattsEventHandler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) {
    switch (event) {
        case ESP_GATTS_WRITE_EVT:
            // Implement write event handling here
            break;
        case ESP_GATTS_READ_EVT:
            // Implement read event handling here
            break;
        case ESP_GATTS_SEND_SERVICE_CHANGE_EVT:
            // Implement handling for the ESP_GATTS_SEND_SERVICE_CHANGE_EVT
            break;
        default:
            // Handle unhandled events
            break;
    }
}
