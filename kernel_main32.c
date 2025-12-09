// kernel/kernel_main32.c - 32-bit entry (before long mode)
#include "screen.h"
#include "shell.h"

extern void jump_to_long_mode();

void kernel_main(void) {
    clear_screen();
    print("Booting MyOS v0.4 - Entering 64-bit mode...\n\n", 0x0A);

    install_idt();
    asm volatile("sti");

    print("Switching to Long Mode...\n", 0x0E);

    // Load GDT, enable paging, jump to 64-bit
    asm volatile("call gdt_load");
    asm volatile("call enable_paging");
    jump_to_long_mode();

    while(1) asm("hlt");
}