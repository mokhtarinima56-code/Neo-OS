// kernel/kernel.c
#include "screen.h"
#include "shell.h"

void kernel_main(void) {
    clear_screen();

    print("MyOS v0.3 - Simple Shell Ready\n\n", 0x0A);
    print("    Welcome! Type 'help' for commands.\n\n", 0x0F);

    install_idt();
    asm volatile("sti");        // Enable interrupts

    shell_print_prompt();
    while (1) asm("hlt");
}