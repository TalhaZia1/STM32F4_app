#ifndef __LOW_POWER_CFG_H
#define __LOW_POWER_CFG_H

#include "stm32f4xx_hal.h"

/**
 * Enters in Normal Sleep Mode on Interrupt IRQ exit Request Only
*/
void sleepOnExitEnable(void);

/**
 * Enters in Wait for Interrupt Power Saving Mode
*/
void WFIEnable(void);

/**
 * isEventRegSet == True -> Clears eventReg
 * isEventRegSet == False -> goes to Power Saving Mode
*/
void WFEEnable(void);


#endif /* __LOW_POWER_CFG_H */