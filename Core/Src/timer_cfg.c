#include "timer_cfg.h"

static TIM_HandleTypeDef htimer6_Base;
static TIM_HandleTypeDef htimer2_IC; 
static uint32_t input_captures[3] ={0};

/* TIM6 High Level Init */
void TIMER6_Init(void) {
	htimer6_Base.Instance = TIM6;
	htimer6_Base.Init.Prescaler = 24;
	htimer6_Base.Init.Period = 64000-1; 
	(void)HAL_TIM_Base_Init(&htimer6_Base);
}

/* TIM6 Low Level Init */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM6) {
		__HAL_RCC_TIM6_CLK_ENABLE();
    	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
		HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 15, 0);
	}
}

void TIMER6_Start(void) {
    (void)HAL_TIM_Base_Start(&htimer6_Base);
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

void TIMER6_Start_IT(void) {
    (void)HAL_TIM_Base_Start_IT(&htimer6_Base);
}

/**
 * TIM6 - IRQ Configuration
*/
void TIM6_DAC_IRQHandler (void) {
	HAL_TIM_IRQHandler(&htimer6_Base);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	static uint8_t count = 0U;
	count++;
	if (count == 10U) {
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		count = 0U;
	} 
}

void TIMER2_Init_IC(void) {
	TIM_IC_InitTypeDef timer2_IC_cfg; 
	htimer2_IC.Instance = TIM2; 
	htimer2_IC.Init.CounterMode = TIM_COUNTERMODE_UP; 
	htimer2_IC.Init.Period = 0xFFFFFFFF; 
	htimer2_IC.Init.Prescaler = 1;
	(void)HAL_TIM_IC_Init(&htimer2_IC);
	timer2_IC_cfg.ICFilter = 0; 
	timer2_IC_cfg.ICPolarity = TIM_ICPOLARITY_RISING;
	timer2_IC_cfg.ICPrescaler = TIM_ICPSC_DIV1;
	timer2_IC_cfg.ICSelection = TIM_ICSELECTION_DIRECTTI;
	HAL_TIM_IC_ConfigChannel(&htimer2_IC, &timer2_IC_cfg, TIM_CHANNEL_1);
}


void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim) {
	GPIO_InitTypeDef tim2ch1_gpio;
	
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	tim2ch1_gpio.Pin = GPIO_PIN_0; 
	tim2ch1_gpio.Mode = GPIO_MODE_AF_PP;
	tim2ch1_gpio.Alternate = GPIO_AF1_TIM2; 
	HAL_GPIO_Init(GPIOA, &tim2ch1_gpio);

	HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(void) {
	HAL_TIM_IRQHandler(&htimer2_IC);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	static uint8_t count = 1;
	if(count == 1) {
		input_captures[0] = __HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_1); 
		count++;
	} else if (count == 2) {
		input_captures[1] = __HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_1);
		count = 1;
		input_captures[2] = input_captures[1] - input_captures[0]; 
		/**
		 * TODO: Getting the Timer Resolution and Computing Input Capture Frequency
		 * input_captures[2] returns no of ticks in Input Capture Mode of Timer
		 * For use case TODO has to be completed. 
		*/
	} 
}

void TIMER2_Start_IC(void) {
    (void)HAL_TIM_IC_Start_IT(&htimer2_IC, TIM_CHANNEL_1);
}
