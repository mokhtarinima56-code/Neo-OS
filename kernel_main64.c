// kernel/kernel_main64.c - Real 64-bit kernel entry
#include "screen.h"
#include "shell.h"

void kernel_main_64(void) {
    clear_screen();

    print("=== MyOS v1.0 - 64-bit Long Mode Active ===\n\n", 0x0A);
    print("    Higher half kernel loaded at 0xFFFFFFFF80000000\n", 0x0E);
    print("    Paging enabled - 4-level page tables\n", 0x0E);
    print("    Full x86-64 architecture\n\n", 0x0E);

    print("Welcome back! Type 'help' for commands.\n\n", 0x0F);

    shell_print_prompt();

    while (1) {
        asm("hlt");
    }
}