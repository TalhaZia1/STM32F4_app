#ifndef __UART_CFG_H
#define __UART_CFG_H

#include "stm32f4xx_hal.h"

/**
 * Buffer Size
*/
#define USART2_TX_BUFFER_SIZE  100
#define USART2_RX_BUFFER_SIZE  100

/**
 * UART2 User Configuration
*/
static UART_HandleTypeDef huart2 = {0};
void UART2_Init(void);
void USART2_IRQHandler (void);

#endif /* __UART_CFG_H */