#ifndef __TIMER_CFG_H
#define __TIMER_CFG_H

#include "stm32f4xx_hal.h"

void TIMER6_Init(void);
void TIMER6_Start(void);
void TIMER6_ledToggle_Polling(void);

#endif /* __TIMER_CFG_H */