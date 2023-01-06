#include "gpio_cfg.h"

void GPIO_LED_Init(void) {
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef led_gpio = {0};
	led_gpio.Pin = GPIO_PIN_5;
	led_gpio.Mode = GPIO_MODE_OUTPUT_PP;
	led_gpio.Pull = GPIO_NOPULL; 
	HAL_GPIO_Init(GPIOA, &led_gpio);
}

void GPIO_BTN_Polling_Init(void) {
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef btn_gpio = {0};
	btn_gpio.Pin = GPIO_PIN_13;
	btn_gpio.Mode = GPIO_MODE_INPUT;
	btn_gpio.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOC, &btn_gpio);
}

void GPIO_BTN_IT_Init(void) {
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef btn_gpio = {0};
	btn_gpio.Pin = GPIO_PIN_13;
	btn_gpio.Mode = GPIO_MODE_IT_FALLING;
	btn_gpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &btn_gpio);
	HAL_NVIC_SetPriority(EXTI15_10_IRQn,15,0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler(void) {
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
