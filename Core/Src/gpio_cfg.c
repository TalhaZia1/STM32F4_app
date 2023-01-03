#include "gpio_cfg.h"

void GPIO_LED_Init(void) {
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef led_gpio;
	led_gpio.Pin = GPIO_PIN_5;
	led_gpio.Mode = GPIO_MODE_OUTPUT_PP;
	led_gpio.Pull = GPIO_NOPULL; 
	(void)HAL_GPIO_Init(GPIOA, &led_gpio);
}