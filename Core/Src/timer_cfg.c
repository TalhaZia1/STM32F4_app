#include "timer_cfg.h"

static TIM_HandleTypeDef htimer6_Base;
static TIM_HandleTypeDef htimer2_IC; 
static TIM_HandleTypeDef htimer2_OC; 
static TIM_HandleTypeDef htimer2_PWM; 
static uint32_t input_captures[3] ={0};
static uint32_t ccr_content;

/**
 * TIMERs BASIC
*/

void TIMER6_Init(void) {
	htimer6_Base.Instance = TIM6;
	htimer6_Base.Init.Prescaler = 24;
	htimer6_Base.Init.Period = 64000-1; 
	(void)HAL_TIM_Base_Init(&htimer6_Base);
}

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

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	static uint8_t count = 0U;
	count++;
	if (count == 10U) {
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		count = 0U;
	} 
}

/**
 * TIMERs INPUT CAPTURE
*/

void TIMER2_Init_IC(void) {
	htimer2_IC.Instance = TIM2; 
	htimer2_IC.Init.CounterMode = TIM_COUNTERMODE_UP; 
	htimer2_IC.Init.Period = 0xFFFFFFFF; 
	htimer2_IC.Init.Prescaler = 1;
	(void)HAL_TIM_IC_Init(&htimer2_IC);
	TIM_IC_InitTypeDef timer2_IC_cfg; 
	timer2_IC_cfg.ICFilter = 0; 
	timer2_IC_cfg.ICPolarity = TIM_ICPOLARITY_RISING;
	timer2_IC_cfg.ICPrescaler = TIM_ICPSC_DIV1;
	timer2_IC_cfg.ICSelection = TIM_ICSELECTION_DIRECTTI;
	HAL_TIM_IC_ConfigChannel(&htimer2_IC, &timer2_IC_cfg, TIM_CHANNEL_1);
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim) {
	if(htim->Instance == TIM2) {
		__HAL_RCC_TIM2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitTypeDef tim2ch1_gpio;
		tim2ch1_gpio.Pin = GPIO_PIN_0; 
		tim2ch1_gpio.Mode = GPIO_MODE_AF_PP;
		tim2ch1_gpio.Alternate = GPIO_AF1_TIM2; 
		HAL_GPIO_Init(GPIOA, &tim2ch1_gpio);
		HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
	}
}

/**
 * @ref HAL_TIM_IC_CaptureCallback()
 * TODO: Getting the Timer Resolution and Computing Input Capture Frequency
 * input_captures[2] returns no of ticks in Input Capture Mode of Timer
 * For use case TODO has to be completed. 
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	static uint8_t count = 1;
	if(count == 1) {
		input_captures[0] = __HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_1); 
		count++;
	} else if (count == 2) {
		input_captures[1] = __HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_1);
		count = 1;
		input_captures[2] = input_captures[1] - input_captures[0]; 
	} 
}

void TIMER2_Start_IC(void) {
    (void)HAL_TIM_IC_Start_IT(&htimer2_IC, TIM_CHANNEL_1);
}

/**
 * TIMERs OUTPUT CAPTURE
*/

/**
 * @ref TIMER2_Init_OC
 * Considering PLL = 50MHz
 * Timer Clock -> 50MHz
 * GPIOA PA0  -> TIM2_CH1 -> 500Hz
 * GPIOA PA1  -> TIM2_CH2 -> 1000Hz 
 * GPIOB PB10 -> TIM2_CH3 -> 2000Hz
 * GPIOB PB2  -> TIM2_CH4 -> 4000Hz
*/
void TIMER2_Init_OC(void) {
	htimer2_OC.Instance = TIM2;
	htimer2_OC.Init.Period = 0xFFFFFFFF;
	htimer2_OC.Init.Prescaler = 1;
	(void)HAL_TIM_OC_Init(&htimer2_OC);
	TIM_OC_InitTypeDef tim2OC_init = {0};
	tim2OC_init.OCMode = TIM_OCMODE_TOGGLE;
	tim2OC_init.OCPolarity = TIM_OCPOLARITY_HIGH;
	tim2OC_init.Pulse = 25000; /* Output Freq -> 500Hz */
	(void)HAL_TIM_OC_ConfigChannel(&htimer2_OC, &tim2OC_init, TIM_CHANNEL_1);
	tim2OC_init.Pulse = 12500; /* Output Freq -> 1000Hz */
	(void)HAL_TIM_OC_ConfigChannel(&htimer2_OC, &tim2OC_init, TIM_CHANNEL_2);
	tim2OC_init.Pulse = 6250; /* Output Freq -> 2000Hz */
	(void)HAL_TIM_OC_ConfigChannel(&htimer2_OC, &tim2OC_init, TIM_CHANNEL_3);
	tim2OC_init.Pulse = 3125; /* Output Freq -> 4000Hz */
	(void)HAL_TIM_OC_ConfigChannel(&htimer2_OC, &tim2OC_init, TIM_CHANNEL_4);
}

void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim) {	
	if(htim->Instance == TIM2) {
		__HAL_RCC_TIM2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitTypeDef tim2ch1_gpios;
		tim2ch1_gpios.Pin = GPIO_PIN_0 | GPIO_PIN_1;
		tim2ch1_gpios.Mode = GPIO_MODE_AF_PP;
		tim2ch1_gpios.Pull = GPIO_NOPULL;
		tim2ch1_gpios.Speed = GPIO_SPEED_FREQ_LOW;
		tim2ch1_gpios.Alternate = GPIO_AF1_TIM2;
		HAL_GPIO_Init(GPIOA, &tim2ch1_gpios);
		__HAL_RCC_GPIOB_CLK_ENABLE();
		tim2ch1_gpios.Pin = GPIO_PIN_2 | GPIO_PIN_10;
		tim2ch1_gpios.Mode = GPIO_MODE_AF_PP;
		tim2ch1_gpios.Pull = GPIO_NOPULL;
		tim2ch1_gpios.Speed = GPIO_SPEED_FREQ_LOW;
		tim2ch1_gpios.Alternate = GPIO_AF1_TIM2;
		HAL_GPIO_Init(GPIOB, &tim2ch1_gpios);
		HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
	}
}

void TIMER2_Start_OC(void) {
    (void)HAL_TIM_OC_Start_IT(&htimer2_OC, TIM_CHANNEL_1);
    (void)HAL_TIM_OC_Start_IT(&htimer2_OC, TIM_CHANNEL_2);
    (void)HAL_TIM_OC_Start_IT(&htimer2_OC, TIM_CHANNEL_3);
    (void)HAL_TIM_OC_Start_IT(&htimer2_OC, TIM_CHANNEL_4);
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
		ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		__HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_1, ccr_content + 25000);
	}
	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
		ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
		__HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_2, ccr_content + 12500);
	}
	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) {
		ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
		__HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_3, ccr_content + 6250);
	}
	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4) {
		ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
		__HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_4, ccr_content + 3125);
	}	
}

/**
 * TIMERs PWM
*/

/**
 * @ref TIMER2_Init_PWM
 * Considering PLL = 50MHz
 * Timer Clk = 50MHz
 * Period PWM -> 1 millisec
 * Channel-1  -> 500Hz
 * Channel-2  -> 500Hz
 * Channel-3  -> 500Hz
 * Channel-4  -> 500Hz
*/
void TIMER2_Init_PWM(void) {
	htimer2_PWM.Instance = TIM2;
	htimer2_PWM.Init.Period = 10000-1;
	htimer2_PWM.Init.Prescaler = 4;
	(void)HAL_TIM_PWM_Init(&htimer2_PWM);
	TIM_OC_InitTypeDef tim2PWM_init = {0};
	tim2PWM_init.OCMode = TIM_OCMODE_PWM1;
	tim2PWM_init.OCPolarity = TIM_OCPOLARITY_HIGH;
	tim2PWM_init.Pulse = htimer2_PWM.Init.Period * 0.25; /*25% Duty Cycle */
	(void)HAL_TIM_PWM_ConfigChannel(&htimer2_PWM, &tim2PWM_init, TIM_CHANNEL_1);
	tim2PWM_init.Pulse = htimer2_PWM.Init.Period * 0.45; /*45% Duty Cycle */
	(void)HAL_TIM_PWM_ConfigChannel(&htimer2_PWM, &tim2PWM_init, TIM_CHANNEL_2);
	tim2PWM_init.Pulse = htimer2_PWM.Init.Period * 0.75; /*75% Duty Cycle */
	(void)HAL_TIM_PWM_ConfigChannel(&htimer2_PWM, &tim2PWM_init, TIM_CHANNEL_3);
	tim2PWM_init.Pulse = htimer2_PWM.Init.Period * 0.90; /*90% Duty Cycle */
	(void)HAL_TIM_PWM_ConfigChannel(&htimer2_PWM, &tim2PWM_init, TIM_CHANNEL_4);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim) {
	if(htim->Instance == TIM2) {
		__HAL_RCC_TIM2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitTypeDef tim2ch1_gpios = {0};
		tim2ch1_gpios.Pin = GPIO_PIN_0 | GPIO_PIN_1;
		tim2ch1_gpios.Mode = GPIO_MODE_AF_PP;
		tim2ch1_gpios.Pull = GPIO_NOPULL;
		tim2ch1_gpios.Speed = GPIO_SPEED_FREQ_LOW;
		tim2ch1_gpios.Alternate = GPIO_AF1_TIM2;
		HAL_GPIO_Init(GPIOA, &tim2ch1_gpios);
		__HAL_RCC_GPIOB_CLK_ENABLE();
		tim2ch1_gpios.Pin = GPIO_PIN_2 | GPIO_PIN_10;
		tim2ch1_gpios.Mode = GPIO_MODE_AF_PP;
		tim2ch1_gpios.Pull = GPIO_NOPULL;
		tim2ch1_gpios.Speed = GPIO_SPEED_FREQ_LOW;
		tim2ch1_gpios.Alternate = GPIO_AF1_TIM2;
		HAL_GPIO_Init(GPIOB, &tim2ch1_gpios);
		HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
	}
}

void TIMER2_Start_PWM(void) {
	(void)HAL_TIM_PWM_Start(&htimer2_PWM, TIM_CHANNEL_1);
    (void)HAL_TIM_PWM_Start(&htimer2_PWM, TIM_CHANNEL_2);
    (void)HAL_TIM_PWM_Start(&htimer2_PWM, TIM_CHANNEL_3);
    (void)HAL_TIM_PWM_Start(&htimer2_PWM, TIM_CHANNEL_4);
}

/**
 * TIMER2 IRQ Handler
*/
void TIM2_IRQHandler(void) {
	//HAL_TIM_IRQHandler(&htimer2_IC);
	HAL_TIM_IRQHandler(&htimer2_OC);
	//HAL_TIM_IRQHandler(&htimer2_PWM);
}

void TIM6_DAC_IRQHandler (void) {
	HAL_TIM_IRQHandler(&htimer6_Base);
}