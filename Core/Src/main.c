#include "stm32f4xx_hal.h"
#include "gpio_cfg.h"
#include "low_power_cfg.h"
#include "uart_cfg.h"
#include "bkup_SRAM_cfg.h"

int main(void) {
	HAL_Init();
	GPIO_BTN_Polling_Init();
	UART2_Init();
	printWelcomeMessage();
	bkup_SRAM_Init();
	while (1);
	return 0; 
}
