#include "bleTask.h"

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

//TODO: to be specified by library
typedef enum {
    BLE_STOPPED = 254,
    BLE_CONNECTED = 3,
    BLE_CONNECT_FAILED = 4,
    BLE_DISCONNECTED = 6
} ble_status;

String bleStatus() {
    //TODO:
    ble_status status = BLE_CONNECTED;

    switch (status) {
    case BLE_CONNECTED:
        return "Connected";
    case BLE_STOPPED:
        return "Stopped";
    case BLE_CONNECT_FAILED:
        return "Connection failed";
    case BLE_DISCONNECTED:
        return "Disconnected";
    default:
        return "UNKNOWN: " + status;
    }
}

void setupBle() {
    // BLEDevice::init("MyESP32");

    // BLEServer *pServer = BLEDevice::createServer();
    // BLEService *pService = pServer->createService(SERVICE_UUID);
    // BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    //     CHARACTERISTIC_UUID, 
    //     BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
    // );

    // pCharacteristic->setValue("Hello World says Neil");
    // pService->start();
    
    // BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    // pAdvertising->addServiceUUID(SERVICE_UUID);
    // pAdvertising->setScanResponse(true);
    // pAdvertising->setMinPreferred(0x06);  
    // pAdvertising->setMinPreferred(0x12);
    // BLEDevice::startAdvertising();
    // Serial.println("Characteristic defined! Now you can read it in your phone!");
}                                         