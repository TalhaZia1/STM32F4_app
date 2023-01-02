#include "clock_cfg.h"

/**
 * TODO: HSE Configuration Settings
 * Configuration Settings are hard coded
 * Function call in main.c @ref HSE_Clock_Config()
*/

void HSE_Clock_Config(void) {

    RCC_OscInitTypeDef osc_init = {0};
	RCC_ClkInitTypeDef clk_init = {0};
	
	/* Switching on HSE */
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState = RCC_HSE_BYPASS;  
	if (HAL_RCC_OscConfig(&osc_init) != HAL_OK) {
		while(1);
	}

	/* Divider Settings */
	clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	clk_init.AHBCLKDivider = RCC_SYSCLK_DIV2;
	clk_init.APB1CLKDivider = RCC_SYSCLK_DIV2;
	clk_init.APB2CLKDivider = RCC_SYSCLK_DIV2;

	/* Switching from HSI to HSE */
	if (HAL_RCC_ClockConfig(&clk_init, FLASH_ACR_LATENCY_0WS) != HAL_OK) {
		while(1);
	} 
	__HAL_RCC_HSI_DISABLE();

	/**
	 * SysTick -> Every 1msec. 
	 * Reconfiguration as of new HCLK
	*/
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

}