#include "bleTask.h"

// https://www.bluetooth.com/wp-content/uploads/Files/Specification/HTML/Assigned_Numbers/out/en/Assigned_Numbers.pdf

#define BATTERY_SERVICE BLEUUID((uint16_t)0x180F)
#define PHYSICAL_ACTIVITY_SERVICE BLEUUID((uint16_t)0x183E)

// Please use camelCase, so first letter of the variable* is small (class names, first letter is big)
BLECharacteristic batteryLevelCharacteristic(BLEUUID((uint16_t)0x2A19), BLECharacteristic::PROPERTY_READ);
BLEDescriptor batteryLevelDescriptor(BLEUUID((uint16_t)0x2901));

BLECharacteristic stepCounterCharacteristic(BLEUUID((uint16_t)0x2B40), BLECharacteristic::PROPERTY_READ);
BLEDescriptor stepCounterDescriptor(BLEUUID((uint16_t)0x2901));

bool _bleClientConnected = false;

class ServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        // Please use debugLog
        debugLog("BLE connected");
        _bleClientConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
        debugLog("BLE disconnected");
        _bleClientConnected = false;
        stopBle();
    };

    void onResult(BLEAdvertisedDevice advertisedDevice) {
        debugLog("Advertised Device: " + advertisedDevice.toString());
    }
};

void _advertiseBattery(BLEServer *pServer) {
    BLEService *pBattery = pServer->createService(BATTERY_SERVICE);
    pBattery->addCharacteristic(&batteryLevelCharacteristic);
    batteryLevelDescriptor.setValue("Percentage of battery charge");
    batteryLevelCharacteristic.addDescriptor(&batteryLevelDescriptor);
    pServer->getAdvertising()->addServiceUUID(BATTERY_SERVICE);
    pBattery->start();
}

void _advertisePhysicalActivity(BLEServer *pServer) {
    BLEService *pPhysicalActivity = pServer->createService(PHYSICAL_ACTIVITY_SERVICE);
    pPhysicalActivity->addCharacteristic(&stepCounterCharacteristic);
    stepCounterDescriptor.setValue("Number of steps");
    stepCounterCharacteristic.addDescriptor(&stepCounterDescriptor);
    pServer->getAdvertising()->addServiceUUID(PHYSICAL_ACTIVITY_SERVICE);
    pPhysicalActivity->start();
}

void initBle() {
    BLEDevice::init(BLUETOOTH_NAME);

    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new ServerCallbacks());
    
    _advertiseBattery(pServer);
    _advertisePhysicalActivity(pServer);

    pServer->getAdvertising()->start();
}

uint8_t betteryLevel = 57;
// uint8_t stepCounter= 42;
uint64_t stepCounter8Bytes = 123456789;

/*
so, battery level works, shows value 57% in nrf connect, cool
but stepCounter shows garbage, why is that?
first, it shows it in hex because there is no standard way to read it, so it simply does hex, battery is standard percentage, so it's not hex
so secondly, 123456789 is in hex 75BCD15

in the app, we see 15-CD-5B-07-00...
Why? Endianness, specifically converted to little endian
So it's fine, just in your app you will need to convert it back (or it will just work, maybe nrf connect forces it, a custom app doesn't), there is no such option in nrf connect (no reason to do it here)
*/

bool isBleClientConnect() {
    return _bleClientConnected;
}

void runBle() {
    batteryLevelCharacteristic.setValue(&betteryLevel, 1);
    // stepCounterCharacteristic.setValue(&stepCounter, 1);
    // Read the arguments to the function, it simply takes bytes and asks how much are there bytes
    stepCounterCharacteristic.setValue((uint8_t*)&stepCounter8Bytes, sizeof(stepCounter8Bytes));
}

void stopBle() {
    BLEDevice::stopAdvertising();
}