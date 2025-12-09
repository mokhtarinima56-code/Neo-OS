; kernel/gdt.asm
[bits 32]
global gdt_load

gdt_start:
    ; Null descriptor
    dq 0x0000000000000000

    ; 64-bit code segment (kernel)
    dq 0x00209A0000000000   ; Present, Ring 0, Code, Executable, 64-bit
    ; 64-bit data segment (kernel)
    dq 0x0000920000000000   ; Present, Ring 0, Data, Writable

    ; 32-bit code segment (for compatibility – optional)
    dq 0x00CF9A000000FFFF
    ; 32-bit data segment
    dq 0x00CF92000000FFFF

gdt_end:

gdt_ptr:
    dw gdt_end - gdt_start - 1
    dd gdt_start
    dq 0  ; 8-byte align for 64-bit

gdt_load:
    lgdt [gdt_ptr]
    ret