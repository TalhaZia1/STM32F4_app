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
