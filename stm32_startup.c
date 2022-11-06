#include <stdint.h>

#define SRAM_START  0x20000000U
#define SRAM_SIZE   (128 * 1024) //128kb
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE))

#define STACK_START SRAM_END 

/***
 * Points to be noted in startup file: 
 * 1) Creation of Vector Table based on MCU specific Reference manual
 * 2) Code initializing .data and .bss section (to be writting in Reset_Handler())
 * 3) Call main()
*/

void Reset_Handler(void);
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));

uint32_t vectors[] = {
    STACK_START,
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&HardFault_Handler,
    (uint32_t)&MemManage_Handler,
    (uint32_t)&BusFault_Handler,
    (uint32_t)&UsageFault_Handler,

    /**
     * TODO: Has to be completed keeing in view of uC reference manual 
    */



}; __attribute__((section(".isr_vector")))


void Default_Handler(void) {
}

void Reset_Handler(void) {
    /* Copy .data section in SRAM */
    /* Init  .bss section to zero in SRAM */
    /* Init fuction of std. library */
    /* call main() */
}