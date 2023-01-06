#include "stm32f4xx_hal.h"
#include "clock_cfg.h"
#include "timer_cfg.h"
#include "gpio_cfg.h"
#include "uart_cfg.h"

int main(void) {
	HAL_Init();
	PLL_Clock_Config();
	UART2_Init();
	printWelcomeMessage();
	TIMER2_Init_PWM();
	TIMER2_Start_PWM();
	while (1) {
		brightnessControl();
	}
	return 0; 
}


