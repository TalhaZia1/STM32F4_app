#include "timer_cfg.h"

static TIM_HandleTypeDef htimer6;

/* TIM6 High Level Init */
void TIMER6_Init(void) {
	htimer6.Instance = TIM6;
	htimer6.Init.Prescaler = 24;
	htimer6.Init.Period = 64000-1; 
	(void)HAL_TIM_Base_Init(&htimer6);
}

/* TIM6 Low Level Init */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim) {
	__HAL_RCC_TIM6_CLK_ENABLE();
    HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 15, 0);
}

void TIMER6_Start(void) {
    HAL_TIM_Base_Start(&htimer6);
}

void TIMER6_ledToggle_Polling(void) {
	static uint8_t count = 0U; 
	while (!(TIM6->SR & TIM_SR_UIF));
	count++; 
	TIM6->SR = 0; 
	if (count == 10U) {
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		count = 0U;
	}

}