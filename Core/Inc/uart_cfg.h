#ifndef __UART_CFG_H
#define __UART_CFG_H

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <string.h>

/**
 * Buffer Size
*/
#define USART2_TX_BUFFER_SIZE  100
#define USART2_RX_BUFFER_SIZE  100

/**
 * UART2 User Configuration
*/
void UART2_Init(void);
void printWelcomeMessage(void);
void printLOG(void);

#endif /* __UART_CFG_H */