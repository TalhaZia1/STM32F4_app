#ifndef __CLOCK_CFG_H
#define __CLOCK_CFG_H

#include "stm32f4xx_hal.h"

void HSE_Clock_Config(void);
void PLL_Clock_Config(void);
void LSE_Clock_Config(void);

#endif /* __CLOCK_CFG_H */