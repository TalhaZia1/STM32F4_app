#ifndef __BKUP_SRAM_CFG_H
#define __BKUP_SRAM_CFG_H

#include "stm32f4xx_hal.h"

void GPIO_LED_Init(void);
void GPIO_BTN_Polling_Init(void);
void GPIO_BTN_IT_Init(void);

#endif /* __BKUP_SRAM_CFG_H */