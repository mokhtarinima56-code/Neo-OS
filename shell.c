// kernel/shell.c - Very simple command-line shell

#include "screen.h"
#include "ports.h"
#include <string.h>   // we will implement strlen/strcmp ourselves

// Simple string functions (no libc)
int strlen(const char* s) {
    int len = 0;
    while (s[len]) len++;
    return len;
}

int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) { s1++; s2++; }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

void reboot(void) {
    print("\nRebooting...\n", 0x0C);  // Light red
    // Trigger warm reboot via keyboard controller
    unsigned char good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
    while(1) asm("hlt");
}

void shell_print_prompt(void) {
    print("MyOS> ", 0x0B);  // Cyan
}

void shell_execute(char* input) {
    if (strcmp(input, "help") == 0) {
        print("\nAvailable commands:\n", 0x0F);
        print("  help   - show this help\n", 0x0A);
        print("  clear  - clear screen\n", 0x0A);
        print("  hello  - greeting message\n", 0x0A);
        print("  info   - OS information\n", 0x0A);
        print("  reboot - restart the system\n", 0x0A);
    }
    else if (strcmp(input, "clear") == 0) {
        clear_screen();
    }
    else if (strcmp(input, "hello") == 0) {
        print("\n    Hello, World!\n    Salam, Jahan!\n\n", 0x0F);
    }
    else if (strcmp(input, "info") == 0) {
        print("\nMyOS v0.3 - Minimal Educational Kernel\n", 0x0E);
        print("Author: You (and Grok)\n", 0x0E);
        print("Architecture: x86 32-bit\n\n", 0x0E);
    }
    else if (strcmp(input, "reboot") == 0) {
        reboot();
    }
    else if (strlen(input) > 0) {
        print("\nUnknown command: ", 0x0C);
        print(input, 0x0C);
        print("\nType 'help' for commands.\n", 0x0F);
    }
}