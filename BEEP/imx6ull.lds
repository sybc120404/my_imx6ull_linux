SECTIONS{
    . = 0x87800000;
    .text :
    {
        BEEP/obj/start.o
        *(.text)
    }
    .rodata ALIGN(4) : {*(.rodata)}
    .data ALIGN(4) : {*(.rodata)}

    . = ALIGN(4);

    __bss_start = .;
    .bss ALIGN(4) : {*(.bss) *(COMMON)}
    __bss_end = .;
}