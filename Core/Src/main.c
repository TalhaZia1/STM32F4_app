#include "stm32f4xx_hal.h"
#include "clock_cfg.h"
#include "timer_cfg.h"

int main(void) {
	HAL_Init();
	PLL_Clock_Config();
	TIMER2_Init_PWM();
	TIMER2_Start_PWM();
	while (1);
	return 0; 
}


