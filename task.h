// kernel/task.h
// Process management and multitasking

#ifndef TASK_H
#define TASK_H

#include <stdint.h>

#define MAX_TASKS 8
#define STACK_SIZE 0x4000  // 16 KB per task

typedef struct {
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, rbp;
    uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
    uint64_t rip, cs, rflags, rsp, ss;
} __attribute__((packed)) registers_t;

typedef struct task {
    registers_t regs;
    uint64_t pid;
    uint64_t rsp;           // kernel stack pointer
    uint64_t stack[STACK_SIZE / 8];
    struct task* next;
} task_t;

void init_multitasking(void);
void create_task(void (*entry)(), uint64_t pid);
void schedule(registers_t* regs);
void yield(void);

#endif