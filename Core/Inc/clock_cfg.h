#ifndef __CLOCK_CFG_H
#define __CLOCK_CFG_H

#include "stm32f4xx_hal.h"

/**
 * TODO: For 180 MHz 
 * Additional Setting of Voltage Regulations -> Overdrive Mode 
 * Scale - 1, Scale - 2, Scale - 3 etc.. 
 * Additional settings are not included. 
 * @ref stm32f4xx_hal_pwr_ex.h
 * @ref stm32f4xx_hal_pwr.h
*/
void HSE_Clock_Config(void);
void PLL_Clock_Config(void);
void LSE_Clock_Config(void);

#endif /* __CLOCK_CFG_H */