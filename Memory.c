// kernel/memory.c
// Simple but solid first-fit kernel heap with coalescing
// Starts at 0xFFFF800010000000 (16 MiB right after kernel image)

#include "memory.h"
#include "screen.h"
#include "ports.h"

#define HEAP_START      0xFFFF800010000000ULL
#define HEAP_SIZE       (16ULL << 24)           // 16 MiB
#define MIN_BLOCK       32

typedef struct block {
    size_t size;          // size of payload (not including header)
    uint8_t used;         // 1 = allocated, 0 = free
    struct block* next;
} __attribute__((packed)) block_t;

static block_t* heap_head = NULL;

void init_memory(void) {
    heap_head = (block_t*)HEAP_START;
    heap_head->size = HEAP_SIZE - sizeof(block_t);
    heap_head->used = 0;
    heap_head->next = NULL;

    print("Kernel heap initialized: 16 MiB @ 0xFFFF800010000000\n", 0x0A);
}

// Align to 16 bytes
static size_t align_up(size_t n) {
    return (n + 15) & ~15;
}

void* kmalloc(size_t size) {
    if (size == 0) return NULL;
    size = align_up(size);
    if (size < MIN_BLOCK) size = MIN_BLOCK;

    block_t* prev = NULL;
    block_t* b = heap_head;

    while (b) {
        if (!b->used && b->size >= size) {
            // Split if possible
            if (b->size >= size + sizeof(block_t) + MIN_BLOCK) {
                block_t* new_block = (block_t*)((uint8_t*)b + sizeof(block_t) + size);
                new_block->size = b->size - size - sizeof(block_t);
                new_block->used = 0;
                new_block->next = b->next;
                b->next = new_block;
                b->size = size;
            }
            b->used = 1;
            return (void*)((uint8_t*)b + sizeof(block_t));
        }
        prev = b;
        b = b->next;
    }
    return NULL; // OOM
}

void* kzalloc(size_t size) {
    void* p = kmalloc(size);
    if (p) {
        uint8_t* ptr = (uint8_t*)p;
        for (size_t i = 0; i < size; i++) ptr[i] = 0;
    }
    return p;
}

void kfree(void* ptr) {
    if (!ptr) return;
    block_t* b = (block_t*)((uint8_t*)ptr - sizeof(block_t));
    b->used = 0;

    // Simple coalesce forward
    block_t* cur = heap_head;
    while (cur && cur->next) {
        if (!cur->used && !cur->next->used) {
            cur->size += cur->next->size + sizeof(block_t);
            cur->next = cur->next->next;
        } else {
            cur = cur->next;
        }
    }
}

// Debug commands
void meminfo(void) {
    print("\n=== Kernel Heap Status ===\n", 0x0E);
    block_t* b = heap_head;
    uint64_t used = 0, free = 0;
    while (b) {
        if (b->used) used += b->size;
        else free += b->size;
        print(b->used ? "[USED] " : "[FREE] ", b->used ? 0x0C : 0x0A);
        print("addr: 0x", 0x0F);
        print_hex((uint64_t)(b + 1), 0x0F);
        print("  size: ", 0x0F);
        print_dec(b->size, 0x0F);
        print(" bytes\n", 0x0F);
        b = b->next;
    }
    print("Total used: ", 0x0C); print_dec(used, 0x0C); print(" bytes\n", 0x0C);
    print("Total free: ", 0x0A); print_dec(free, 0x0A); print(" bytes\n", 0x0A);
}

void memtest(void) {
    print("\nMemory allocation stress test...\n", 0x0E);
    void* a = kmalloc(1024);
    void* b = kmalloc(8192);
    void* c = kzalloc(32768);
    print("Allocated 1KB + 8KB + 32KB(zeroed)\n", 0x0A);
    kfree(b);
    print("Freed 8KB block\n", 0x0A);
    void* d = kmalloc(6000);
    print(d ? "Reused freed block → success!\n" : "Reuse failed!\n", d ? 0x0A : 0x0C);
    meminfo();
}