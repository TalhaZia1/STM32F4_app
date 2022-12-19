ENTRY(Reset_Handler)

/*
* Linker script for MCU - Depending on the board 
* Copied from STM32CubeIDE
*/

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