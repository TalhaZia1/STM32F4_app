#include "bkup_SRAM_cfg.h"

void bkup_SRAM_Init(void) {
    uint32_t* pBkupSRAM = (uint32_t*)BKPSRAM_BASE;
	char write_buf[] = "Hello";
	__HAL_RCC_BKPSRAM_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnableBkUpAccess();
	/* strlen + 1 for null termination */
	for(uint32_t i = 0; i < strlen(write_buf) + 1; i++) {
		*(pBkupSRAM+i) = write_buf[i];
	}
}
