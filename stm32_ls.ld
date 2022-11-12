ENTRY(Reset_Handler)

/* Depends on MCU can be copied from STM32CubeIDE as reference */

MEMORY {
    FLASH(rx):ORIGIN=0x08000000,LENGTH=512K
    SRAM1(rwx):ORIGIN=0x20000000,LENGTH=128K
    BAKSRAM(rwx):ORIGIN=0x20000000+128K-4, LENGTH=4K
}

SECTIONS {
    .text:{
        *(.isr_vector)
        *(.text)
        *(.rodata)
    }> FLASH AT> FLASH 
    .data:{
        
    }
}