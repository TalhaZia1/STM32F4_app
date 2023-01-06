#include "low_power_cfg.h"

void sleepOnExitEnable(void) {
    HAL_PWR_EnableSleepOnExit();
}

void WFIEnable(void) {
    __WFI();
}

void WFEEnable(void) {
    __WFE();
}