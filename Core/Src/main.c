#include "main.h"
#include "stm32f4xx_hal.h"

void SystemClock_Config(void);

int main(void) {
  
  HAL_Init();
  SystemClock_Config();
  
  while (1) {


  }
  
  return 0; 
}

void SystemClock_Config(void) {

}



