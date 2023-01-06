#include "stm32f4xx_hal.h"
#include "gpio_cfg.h"
#include "low_power_cfg.h"

int main(void) {
	HAL_Init();
	GPIO_LED_Init();
	GPIO_BTN_IT_Init();
	while (1) {
		WFIEnable();
	}
	return 0; 
}
