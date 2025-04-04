#include "bleTask.h"

#define BatteryService BLEUUID((uint16_t)0x180F)

BLECharacteristic BatteryLevelCharacteristic(BLEUUID((uint16_t)0x2A19), BLECharacteristic::PROPERTY_READ);
BLEDescriptor BatteryLevelDescriptor(BLEUUID((uint16_t)0x2901));

bool _bleClientConnected = false;
class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        Serial.println("connected");
        _bleClientConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
        Serial.println("disconnected");
        _bleClientConnected = false;
    };

    void onResult(BLEAdvertisedDevice advertisedDevice) {
        Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

void initBle() {
    BLEDevice::init(BLUETOOTH_NAME);

    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    
    BLEService *pBattery = pServer->createService(BatteryService);
    pBattery->addCharacteristic(&BatteryLevelCharacteristic);
    BatteryLevelDescriptor.setValue("Percentage 0 - 100");
    BatteryLevelCharacteristic.addDescriptor(&BatteryLevelDescriptor);
    pServer->getAdvertising()->addServiceUUID(BatteryService);
    pBattery->start();

    pServer->getAdvertising()->start();
}

uint8_t level = 57;

bool isClientConnect() {
    return _bleClientConnected;
}

void runBle() {
    BatteryLevelCharacteristic.setValue(&level, 1);
}

void stopBle() {
    BLEDevice::deinit(true);
}