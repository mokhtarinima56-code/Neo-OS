// kernel/timer.c
// Programmable Interval Timer (PIT) at ~100 Hz

#include "ports.h"

void init_timer(void) {
    // 100 Hz = 1193182 / 100 = 11931
    uint16_t divisor = 11931;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);
    print("PIT initialized @ ~100Hz\n", 0x0A);
}