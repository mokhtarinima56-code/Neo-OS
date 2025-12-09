// kernel/keyboard.c - now feeds a command line buffer

#include "screen.h"
#include "shell.h"

#define MAX_INPUT 256

static char input_buffer[MAX_INPUT];
static int input_pos = 0;

static char scancode_to_ascii[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1',
    '2', '3', '0', '.'
};

void keyboard_handler(void) {
    unsigned char sc = inb(0x60);

    if (sc & 0x80) return;  // ignore key release

    char c = scancode_to_ascii[sc];

    if (c == '\b') {  // Backspace
        if (input_pos > 0) {
            input_pos--;
            input_buffer[input_pos] = 0;
            // Simple backspace on screen
            print("\b \b", 0x0F);
        }
    }
    else if (c == '\n') {
        print("\n", 0x0F);
        input_buffer[input_pos] = 0;
        shell_execute(input_buffer);
        input_pos = 0;
        shell_print_prompt();
    }
    else if (c != 0 && input_pos < MAX_INPUT-1) {
        input_buffer[input_pos++] = c;
        char temp[2] = {c, 0};
        print(temp, 0x0F);
    }

    outb(0x20, 0x20);  // EOI
}