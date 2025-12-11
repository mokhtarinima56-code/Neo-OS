// kernel/elf.h
#ifndef ELF_H
#define ELF_H

int load_elf(const char* path);

#endif


#include "elf.h"
#include "screen.h"
#include "task.h"
#include "memory.h"

int load_elf(const char* path) {
    // TODO: Read ELF from RAM disk (for now fake)
    print("Loading ELF: ", 0x0A);
    print(path, 0x0A);
    print("\n", 0x0A);

    // Fake entry point
    uint64_t entry = 0x400000;
    create_task((void(*)())entry, 3);  // New user task
    return 0;
}