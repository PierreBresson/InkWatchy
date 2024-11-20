#include "debug.h"

#if DEBUG && EINK_COUNTER
#define SKIP_CYCLES 7
bool randomChoosed = false;
int counterX;
int counterY;
int countSkip = SKIP_CYCLES;
int RTC_DATA_ATTR counter = 0;
void showEinkCounter()
{
    debugLog("countSkip: " + String(countSkip));
    if (countSkip == SKIP_CYCLES)
    {
        countSkip = 0;
        setTextSize(2);
        if (randomChoosed == false)
        {
            randomChoosed = true;
            counterX = random(50, 150);
            counterY = random(150, 180);
        }
        display.setCursor(counterX, counterY);
        counter = counter + 1;
        debugLog("Showing einkCounter: " + String(counter));
        writeTextReplaceBack(String(counter), counterX, counterY);
        disUp(true);
    }
    countSkip = countSkip + 1;
}
#endif
