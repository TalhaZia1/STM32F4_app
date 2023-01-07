#ifndef __GPIO_CFG_H
#define __GPIO_CFG_H

#include "stm32f4xx_hal.h"

void GPIO_LED_Init(void);
void GPIO_BTN_Polling_Init(void);
void GPIO_BTN_IT_Init(void);

#endif /* __GPIO_CFG_H */