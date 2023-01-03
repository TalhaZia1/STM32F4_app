#include "stm32f4xx_hal.h"
#include "gpio_cfg.h"
#include "timer_cfg.h"



int main(void) {
	HAL_Init();
	GPIO_LED_Init();
	TIMER6_Init();
	TIMER6_Start();
	while (1) {
		TIMER6_ledToggle_Polling();
	}
	return 0; 
}
