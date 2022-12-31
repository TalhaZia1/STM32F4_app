#include "stm32f4xx_hal.h"

/**
 * TODO: Low level Processor Specific Inits 
 * -> Priority Grouping of ARM Cortex MX Processor
 * -> Enabling required system exceptions 
 * -> Configuring priority for system exceptions 
*/

void HAL_MspInit(void) {
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
    SCB->SHCSR |= 0x7 << 16; 
    HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
    HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
    HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

/**
 * TODO: Low Level Init -> USART2 Peripheral
 * -> Clock Enable
 * -> Pin Muxing
 * -> Enabling IRQ and setup Priority (NVIC Setting)
*/

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
    __HAL_RCC_USART2_CLK_ENABLE();
    
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