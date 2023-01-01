#include "main.h"

void SystemClock_Config(void);
void UART2_Init(void); 
void Error_handler(void);

UART_HandleTypeDef huart2;

char *data = "The application is running\r\n";

int main(void) {
	HAL_Init();
	SystemClock_Config();
	UART2_Init();
	uint16_t length = strlen(data);
	if (HAL_UART_Transmit(&huart2, (uint8_t*) data, length, HAL_MAX_DELAY) != HAL_OK) {
		Error_handler();
	}
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

