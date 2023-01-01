#include "main.h"

void SystemClock_Config(void);
void UART2_Init(void); 
void Error_handler(void);

UART_HandleTypeDef huart2;


int main(void) {
	HAL_Init();
	SystemClock_Config();
	UART2_Init();

	uint8_t command;
	uint8_t rx_buffer[100];
	uint32_t count = 0U;

	while(1) {
		(void)HAL_UART_Receive(&huart2, &command, 1, HAL_MAX_DELAY);
		if (command == '\r') {
			break;
		} else {
			rx_buffer[count] = command;
			count++;
		}
	} 

	(void)HAL_UART_Transmit(&huart2, (uint8_t *)rx_buffer, count, HAL_MAX_DELAY);

	while (1);
	return 0; 
}

void SystemClock_Config(void) {

}

void UART2_Init(void) {
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if ( HAL_UART_Init(&huart2) != HAL_OK ) {
		Error_handler();
	}
}

void Error_handler(void) {
	while(1);
}

