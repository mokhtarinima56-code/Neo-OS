; kernel/long_mode_init.asm
[bits 32]
global jump_to_long_mode

extern kernel_main_64

section .text
jump_to_long_mode:
    ; Load 64-bit GDT
    lgdt [gdt_ptr_64]

    ; Far jump to 64-bit code segment
    jmp 0x08:long_mode_start

[bits 64]
long_mode_start:
    ; Set segment registers
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Jump to C 64-bit kernel
    mov rax, kernel_main_64
    call rax

    ; Should never return
    cli
    hlt
    jmp $

section .data
gdt_ptr_64:
    dw gdt_end - gdt_start - 1
    dq gdt_start