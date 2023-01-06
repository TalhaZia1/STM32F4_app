#include "stm32f4xx_hal.h"
#include "clock_cfg.h"
#include "gpio_cfg.h"
#include "uart_cfg.h"

int main(void) {
	HAL_Init();
	UART2_Init();
	printWelcomeMessage();
	while (1);
	return 0; 
}


