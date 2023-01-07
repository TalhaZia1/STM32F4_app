#ifndef __BKUP_SRAM_CFG_H
#define __BKUP_SRAM_CFG_H

#include "stm32f4xx_hal.h"
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

/**
 * Dummy Implementation of Backup SRAM
 * BK_SRAM -> 4kB
 * BKPSRAM_BASE -> Base Address
 * TODO: Get data, write data -> APIs are pending
*/
void bkup_SRAM_Init(void);

#endif /* __BKUP_SRAM_CFG_H */