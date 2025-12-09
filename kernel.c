// kernel/kernel.c
#include "screen.h"
#include "idt.c"         // We will split later; for now include
#include "keyboard.c"

void kernel_main(void) {
    clear_screen();

    print("Booting MyOS v0.2 - Keyboard Ready\n\n", 0x0A);
    print("    Hello, World!\n", 0x0F);
    print("    Salam, Jahan!\n\n", 0x0F);
    print(">>> Start typing (US layout) <<<\n\n", 0x0B);

    install_idt();           // Enable keyboard interrupts

    // Enable interrupts
    asm volatile("sti");

    while (1) {
        asm volatile("hlt");
    }
}