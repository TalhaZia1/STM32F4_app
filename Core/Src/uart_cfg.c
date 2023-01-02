#include "uart_cfg.h"

/**
 * TODO: High Level Init -> USART Pheripheral
 * Function call in main.c for usage
*/

void UART2_Init(void) {
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if (HAL_UART_Init(&huart2) != HAL_OK ) {
		while(1);
	}
}

/**
 * TODO: Low Level Init -> USART Peripheral
*/

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
    
    /* USART2 - LOW LEVEL INIT */
    if (huart->Instance == USART2) {
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        /**
         * TX - GPIOA - PIN 2
         * RX - GPIOA - PIN 3 
        */
        GPIO_InitTypeDef gpio_uart;
        gpio_uart.Pin = GPIO_PIN_2; 
        gpio_uart.Mode = GPIO_MODE_AF_PP;
        gpio_uart.Pull = GPIO_PULLUP; 
        gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
        gpio_uart.Alternate = GPIO_AF7_USART2; 
        HAL_GPIO_Init(GPIOA, &gpio_uart); 
        gpio_uart.Pin = GPIO_PIN_3; 
        HAL_GPIO_Init(GPIOA, &gpio_uart);

        /* USART2 - Interrupt Enabling */
        HAL_NVIC_EnableIRQ(USART2_IRQn); 
        HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);
    }
}

/**
 * USART2 - IRQ Configuration
*/
void USART2_IRQHandler (void) {
    HAL_UART_IRQHandler(&huart2); 
}


