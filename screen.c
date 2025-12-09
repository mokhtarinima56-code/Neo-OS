// kernel/screen.c
#include "screen.h"

#define VGA_BUFFER 0xB8000
#define VGA_WIDTH  80

static unsigned short* vga = (unsigned short*)VGA_BUFFER;
static int cursor_pos = 0;

void clear_screen(void) {
    cursor_pos = 0;
    for (int i = 0; i < 80*25; i++) {
        vga[i] = (0x07 << 8) | ' ';
    }
}

void print(const char* str, unsigned char color) {
    while (*str) {
        if (*str == '\n') {
            cursor_pos += VGA_WIDTH - (cursor_pos % VGA_WIDTH);
        } else {
            vga[cursor_pos] = (color << 8) | *str;
            cursor_pos++;
        }
        str++;
    }
}