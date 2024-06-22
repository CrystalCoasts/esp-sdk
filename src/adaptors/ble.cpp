#include "ble.h"

Ble* Ble::ble = nullptr;
Ble& ble = Ble::Get();

Ble::Ble() {status = BleStatus::OFF;}

void Ble::init() {
    // Initialize BLE stack

    nvs_flash_init();
    nimble_port_init();

    ble_svc_gap_device_name_set("SEAWALL-0");
    ble_svc_gap_init();
    ble_svc_gatt_init();

    //set callsback for ble events
    ble_hs_cfg.sync_cb = Ble::on_sync;
    nimble_port_freertos_init(Ble::host_task);

    
    status = BleStatus::ON; 

}
void host_task(void *param)
{
    nimble_port_run();
}

void host_task(void *param)
{
    nimble_port_run();
}

void Ble::on_sync(void)
{
    // Automatically infer the best address type to use (public or random).
    ble_hs_id_infer_auto(0, &Ble::ble_addr_type);

    // Start advertising with the inferred address type.
    Ble::Get().startAdvertising();
}

void Ble::startAdvertising(void)
{
    struct ble_hs_adv_fields fields;
    memset(&fields, 0, sizeof(fields));

    fields.flags = BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_DISC_LTD;
    fields.tx_pwr_lvl_is_present = 1;
    fields.tx_pwr_lvl = BLE_HS_ADV_TX_PWR_LVL_AUTO;

    fields.name = (uint8_t *)ble_svc_gap_device_name();
    fields.name_len = strlen(ble_svc_gap_device_name());
    fields.name_is_complete = 1;

    ble_gap_adv_set_fields(&fields);

    struct ble_gap_adv_params adv_params;
    memset(&adv_params, 0, sizeof(adv_params));
    adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
    adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;

    ble_gap_adv_start(ble_addr_type, NULL, BLE_HS_FOREVER, &adv_params, ble_app_gap_event, NULL);
}



int Ble::ble_app_gap_event(struct ble_gap_event *event, void *arg) {
    switch (event->type) {
        case BLE_GAP_EVENT_CONNECT:
            if (event->connect.status == 0) { // Connection successful
                ble_gap_conn_desc conn_desc;
                ble_gap_conn_find(event->connect.conn_handle, &conn_desc);
                // Initiate security request to start bonding
                ble_gap_security_initiate(conn_desc.conn_handle);
            }
            break;
        
        case BLE_GAP_EVENT_DISCONNECT:
            break;

        case BLE_GAP_EVENT_ADV_COMPLETE:
            break;

        case BLE_GAP_EVENT_SUBSCRIBE:
            break;

       default :
            break;
    }
    return 0; // Return 0 to indicate successful handling of the event
}

