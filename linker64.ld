ENTRY(_start)

SECTIONS
{
    . = 0xFFFFFFFF80000000;     /* Kernel lives in higher half */

    .text : {
        *(.text)
        *(.rodata*)
    }

    .data : { *(.data) }
    .bss  : { *(.bss) *(COMMON) }
}