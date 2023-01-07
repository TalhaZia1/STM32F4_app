#ifndef __LOW_POWER_CFG_H
#define __LOW_POWER_CFG_H

#include "stm32f4xx_hal.h"

/**
 * Enters in Normal Sleep Mode on Interrupt IRQ exit Request Only
*/
void sleepOnExitEnable(void);

/**
 * Wait for Interrupt -> Power Saving Mode
*/
void WFIEnable(void);

/**
 * isEventRegSet == True -> Clears eventReg
 * isEventRegSet == False -> goes to Power Saving Mode
 * TODO: WFE instruction use in Reference Manual
*/
void WFEEnable(void);

/**
 * Requred for 180MHz clock
 * @ref stm32f4xx_hal_pwr_ex.h
 * @ref stm32f4xx_hal_pwr.h
*/
void overDrivePWREnable(void);

#endif /* __LOW_POWER_CFG_H */