#include "low_power_cfg.h"

void sleepOnExitEnable(void) {
    HAL_PWR_EnableSleepOnExit();
}