// kernel/syscall.c - System call dispatcher for x86-64

#include "syscall.h"
#include "task.h"
#include "screen.h"
#include "elf.h"  // We'll add ELF next

long syscall(long number, ...) {
    switch (number) {
        case SYS_EXIT:
            print("User process exited\n", 0x0A);
            // TODO: Cleanup and schedule next
            while (1) asm("hlt");
            break;
        case SYS_FORK:
            print("Fork called - creating child\n", 0x0E);
            // TODO: Implement fork (copy PCB)
            return 42;  // Fake PID
        case SYS_EXEC:
            print("Exec called - loading ELF\n", 0x0E);
            // TODO: Load ELF from path
            return 0;
        case SYS_WRITE:
            print("User write: Hello from user mode!\n", 0x0F);
            return 13;
        default:
            print("Unknown syscall\n", 0x0C);
            return -1;
    }
    return 0;
}