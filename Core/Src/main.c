#include "stm32f4xx_hal.h"

static TIM_HandleTypeDef htimer2_OC; 
void TIMER2_Init_OC(void); 
void TIMER2_Start_OC(void);

int main(void) {
	HAL_Init();
	while (1);
	return 0; 
}

