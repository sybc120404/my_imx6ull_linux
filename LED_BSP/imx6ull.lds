SECTIONS{
    . = 0x87800000;
    .text :
    {
        LED_BSP/obj/start.o
        *(.text)
    }
    .rodata ALIGN(4) : {*(.rodata)}
    .data ALIGN(4) : {*(.rodata)}

    __bss_start = .;
    .bss ALIGN(4) : {*(.bss) *(COMMON)}
    __bss_end = .;
}