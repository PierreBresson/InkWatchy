#include "bleDebug.h"

// Idk what these are for, so I will leave them, but any function turning on bluetooth should take true as on and off as false, if a function below, outside of
// our control does that, then we switch it in the function there, not here in the UI
// #define BLE_ON 0
// #define BLE_OFF 1

#define CURSOR_X_BLE 0
#define BLE_TEXT_SIZE 1

int bleStatusHeight;
bool isBleConnected = false;

String bleStatusToStr(bool connected) {
    if(connected == true) {
        return "Connected";
    }
    return "Disconnected";
}

void initBleDebugDisplay() {
    setFont(&FreeSansBold9pt7b);
    setTextSize(BLE_TEXT_SIZE);
    dis->setTextWrap(false);
    dis->setCursor(CURSOR_X_BLE, 1);
    String menuName = "Debug Menu";
    getTextBounds(menuName, NULL, NULL, NULL, &maxHeight);

    uint16_t currentHeight = maxHeight;
    maxHeight = maxHeight + 1;
    dis->setCursor(CURSOR_X_BLE, currentHeight - 3);
    dis->print(menuName);

    dis->fillRect(0, currentHeight, dis->width(), 3, GxEPD_BLACK);
    currentHeight = currentHeight + maxHeight;
    centerText("Bluetooth name:", &currentHeight);

    // NOTE: BLUETOOTH_NAME max length is 32 bytes, forced below in sdkconfig. After adding it in config.h, paste this note there
    centerText(String(BLUETOOTH_NAME), &currentHeight);

    centerText("Status:", &currentHeight);

    bleStatusHeight = currentHeight;
    centerText(bleStatusToStr(isBleClientConnect()), &currentHeight);

    disUp(true);

    runBle(); // It's in init because we don't need to call it so many times, right? also it should probably be run in initBle but idk

    initBle();
}

void loopBleDebugDisplay() {
    bool isBleConnectedTmp = isBleClientConnect();
    if(isBleConnectedTmp != isBleConnected) {
        isBleConnected = isBleConnectedTmp;
        dUChange = true;
        writeTextCenterReplaceBack(bleStatusToStr(isBleConnected), bleStatusHeight);
    } 
    
    disUp();
    resetSleepDelay();
}

void stopBleDebug() {
    stopBle();
}