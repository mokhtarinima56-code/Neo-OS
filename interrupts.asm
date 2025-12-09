; kernel/interrupts.asm - ISR for keyboard (IRQ1 → interrupt 33)

[bits 32]
extern keyboard_handler     ; C function we will write

global irq1_handler
irq1_handler:
    pushad                  ; Save all general-purpose registers
    cld
    call keyboard_handler   ; Call C handler
    popad
    iret                    ; Return from interrupt