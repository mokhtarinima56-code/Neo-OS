// kernel/keyboard.c - Very simple US keyboard handler
#include "screen.h"

static char scancode_to_ascii[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1',
    '2', '3', '0', '.'
};

void keyboard_handler(void) {
    unsigned char scancode = inb(0x60);

    if (scancode & 0x80) {
        // Key release - ignore for now ignore
    } else {
        char c = scancode_to_ascii[scancode];
        if (c != 0) {
            char str[2] = {c, 0};
            print(str, 0x0F);        // Bright white
        }
    }

    // Send EOI (End of Interrupt) to PIC
    outb(0x20, 0x20);
}