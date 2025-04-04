#include "bleTask.h"

#define BatteryService BLEUUID((uint16_t)0x180F)
#define PhysicalActivityService BLEUUID((uint16_t)0x183E)

BLECharacteristic BatteryLevelCharacteristic(BLEUUID((uint16_t)0x2A19), BLECharacteristic::PROPERTY_READ);
BLEDescriptor BatteryLevelDescriptor(BLEUUID((uint16_t)0x2901));

BLECharacteristic StepCounterCharacteristic(BLEUUID((uint16_t)0x2B40), BLECharacteristic::PROPERTY_READ);
BLEDescriptor StepCounterDescriptor(BLEUUID((uint16_t)0x2901));

bool _bleClientConnected = false;
class ServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        Serial.println("connected");
        _bleClientConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
        Serial.println("disconnected");
        _bleClientConnected = false;
        stopBle();
    };

    void onResult(BLEAdvertisedDevice advertisedDevice) {
        Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

void _advertiseBattery(BLEServer *pServer) {
    BLEService *pBattery = pServer->createService(BatteryService);
    pBattery->addCharacteristic(&BatteryLevelCharacteristic);
    BatteryLevelDescriptor.setValue("Percentage 0 - 100");
    BatteryLevelCharacteristic.addDescriptor(&BatteryLevelDescriptor);
    pServer->getAdvertising()->addServiceUUID(BatteryService);
    pBattery->start();
}

void _advertisePhysicalActivity(BLEServer *pServer) {
    BLEService *pPhysicalActivity = pServer->createService(PhysicalActivityService);
    pPhysicalActivity->addCharacteristic(&StepCounterCharacteristic);
    StepCounterDescriptor.setValue("Number of steps");
    StepCounterCharacteristic.addDescriptor(&StepCounterDescriptor);
    pServer->getAdvertising()->addServiceUUID(PhysicalActivityService);
    pPhysicalActivity->start();
}

void initBle() {
    Serial.println("initBle");
    BLEDevice::init(BLUETOOTH_NAME);

    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new ServerCallbacks());
    
    _advertiseBattery(pServer);
    _advertisePhysicalActivity(pServer);

    pServer->getAdvertising()->start();
}

uint8_t betteryLevel = 57;
int stepCounter = 1742;

bool isClientConnect() {
    return _bleClientConnected;
}

void runBle() {
    BatteryLevelCharacteristic.setValue(&betteryLevel, 1);
    StepCounterCharacteristic.setValue(stepCounter);
}

void stopBle() {
    BLEDevice::stopAdvertising();
    BLEDevice::deinit(true);
}