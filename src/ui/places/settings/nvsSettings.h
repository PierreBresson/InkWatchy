#ifndef NVS_SETTING_H
#define NVS_SETTING_H

#include "../../defines/defines.h"

extern bool disableAllVibration;
extern bool disableWakeUp;

void loadAllStorage();
void saveAllStorage();

void toggleAllVibration();
void toggleWakeUp();

#endif
