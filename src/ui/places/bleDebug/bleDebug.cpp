#include "bleDebug.h"

#define BLE_ON 0
#define BLE_OFF 1
#define cursorXble 0
#define TextSize 1

int bleActivated = 0;
int bleStatusHeight;
uint16_t bluetoothNameHeight;
String bleName;
String lastBleStatus;
cordInfo buttonCord;

void initBleDebugDisplay() {
    setFont(&FreeSansBold9pt7b);
    setTextSize(TextSize);
    dis->setTextWrap(false);
    dis->setCursor(cursorXble, 1);
    String menuName = "Debug Menu: BLE";
    getTextBounds(menuName, NULL, NULL, NULL, &maxHeight);

    uint16_t currentHeight = maxHeight;
    maxHeight = maxHeight + 1;
    dis->setCursor(cursorXble, currentHeight - 3);
    dis->print(menuName);

    dis->fillRect(0, currentHeight, dis->width(), 3, GxEPD_BLACK);
    currentHeight = currentHeight + maxHeight;
    centerText("Bluetooth name:", &currentHeight);

    bleName = BLUETOOTH_NAME;
    bluetoothNameHeight = currentHeight;
    centerText(bleName, &currentHeight);

    initBle();

    disUp(true);
}

void loopBleDebugDisplay() {
    runBle();

    setFont(&FreeSansBold9pt7b);
    setTextSize(TextSize);
    dis->setTextWrap(false);
    dis->setCursor(cursorXble, 1);
    String menuName = "Debug Menu: BLE";
    getTextBounds(menuName, NULL, NULL, NULL, &maxHeight);

    uint16_t currentHeight = maxHeight;
    maxHeight = maxHeight + 1;
    dis->setCursor(cursorXble, currentHeight - 3);
    dis->print(menuName);

    dis->fillRect(0, currentHeight, dis->width(), 3, GxEPD_BLACK);
    currentHeight = currentHeight + maxHeight;
    centerText("Bluetooth name:", &currentHeight);

    bleName = BLUETOOTH_NAME;
    bluetoothNameHeight = currentHeight;
    centerText(bleName, &currentHeight);

    centerText("Bluetooth status: ", &currentHeight);
    lastBleStatus = isClientConnect() ? "Connected":"Disconnected";

    centerText(lastBleStatus, &currentHeight);
    bleStatusHeight = currentHeight - maxHeight;

    disUp(true);
}

// release memory and save energy
void stopBleDebug() {
    stopBle();
}