#ifndef SLEEP_H
#define SLEEP_H

#include "../defines/defines.h"

void goSleep();
void ForceInputs();
void manageSleep();
uint64_t pinToMask(uint8_t pin);

#endif
