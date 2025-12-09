// kernel/idt.c - Interrupt Descriptor Table setup
#include "ports.h"

#define IDT_ENTRIES 256

struct idt_entry {
    unsigned short base_low;
    unsigned short sel;         // Kernel segment
    unsigned char  always0;
    unsigned char  flags;
    unsigned short base_high;
} __attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned int   base;
} __attribute__((packed));

struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr   idtp;

extern void load_idt(unsigned int);

// Port byte out
void outb(unsigned short port, unsigned char val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

// Set an entry in the IDT
void idt_set_gate(unsigned char num, unsigned int base, unsigned short sel, unsigned char flags) {
    idt[num].base_low  = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel       = sel;
    idt[num].always0   = 0;
    idt[num].flags     = flags | 0x60;  // User DPL=3? No, kernel → 0x8E
}

// Initialize IDT and remap PIC
void install_idt(void) {
    idtp.limit = (sizeof(struct idt_entry) * IDT_ENTRIES) - 1;
    idtp.base  = (unsigned int)&idt;

    // Clear IDT
    for (int i = 0; i < IDT_ENTRIES; i++)
        idt_set_gate(i, 0, 0x08, 0);

    // Remap PIC: IRQ0-7 → 0x20-0x27, IRQ8-15 → 0x28-0x2F
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    // Install keyboard handler (IRQ1 → INT 0x21)
    idt_set_gate(33, (unsigned int)irq1_handler, 0x08, 0x8E);

    load_idt((unsigned int)&idtp);
}