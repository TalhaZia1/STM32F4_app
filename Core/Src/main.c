#include "stm32f4xx_hal.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

static void task1_handler(void* parameter);
static void task2_handler(void* parameter);

int main(void) {
	TaskHandle_t task1_handle; 
	TaskHandle_t task2_handle; 
	BaseType_t status;
	status = xTaskCreate(task1_handler, "Task-1", 200, "Hello World from Task-1", 2, &task1_handle);
	configASSERT(status == pdPASS); 
	
	status = xTaskCreate(task2_handler, "Task-2", 200, "Hello World from Task-2", 2, &task2_handle);
	configASSERT(status == pdPASS); 
	
	while (1);
	return 0; 
}

static void task1_handler(void* parameter) {

}

static void task2_handler(void* parameter) {

}
