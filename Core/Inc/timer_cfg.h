#ifndef __TIMER_CFG_H
#define __TIMER_CFG_H

#include "stm32f4xx_hal.h"

void TIMER6_Init(void);
void TIMER6_Start(void);
void TIMER6_ledToggle_Polling(void);
void TIMER6_Start_IT(void);

void TIMER2_Init_IC(void); 
void TIMER2_Start_IT(void);

#endif /* __TIMER_CFG_H */