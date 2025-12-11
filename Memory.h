// kernel/memory.h
// Kernel memory management — physical frame allocator + heap (kmalloc/kfree)

#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

void init_memory(void);

// Standard kernel allocation
void* kmalloc(size_t size);
void* kzalloc(size_t size);   // zero-initialized
void  kfree(void* ptr);

// Debug / shell commands
void meminfo(void);   // show heap status
void memtest(void);   // allocation stress test

#endif