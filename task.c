// kernel/task.c
// Simple round-robin multitasking with PIT timer

#include "task.h"
#include "screen.h"
#include "ports.h"

static task_t* current_task = NULL;
static task_t* task_list = NULL;
static uint64_t next_pid = 1;

void task_entry_wrapper(void (*func)()) {
    func();
    print("\nTask terminated.\n", 0x0C);
    while (1) asm("hlt");
}

void create_task(void (*entry)(), uint64_t pid) {
    task_t* t = (task_t*)kmalloc(sizeof(task_t));
    if (!t) return;

    // Setup stack
    uint64_t* stack_top = &t->stack[STACK_SIZE / 8];
    *--stack_top = (uint64_t)entry;           // return address
    *--stack_top = 0x10;                      // SS
    *--stack_top = (uint64_t)stack_top;       // RSP
    *--stack_top = 0x202;                     // RFLAGS (interrupts enabled)
    *--stack_top = 0x08;                      // CS
    t->regs.rip = (uint64_t)task_entry_wrapper;

    t->regs.rsp = (uint64_t)stack_top;
    t->regs.rbp = (uint64_t)stack_top;
    t->pid = pid ? pid : next_pid++;
    t->next = task_list;
    task_list = t;

    print("Task created PID ", 0x0A);
    print_dec(t->pid, 0x0A);
    print("\n", 0x0F);
}

void schedule(registers_t* regs) {
    if (!current_task) {
        current_task = task_list;
        if (!current_task) return;
    }

    // Save current context
    __builtin_memcpy(&current_task->regs, regs, sizeof(registers_t));

    // Move to next task
    current_task = current_task->next ? current_task->next : task_list;

    // Restore next task context
    __builtin_memcpy(regs, ¤t_task->regs, sizeof(registers_t));
}

// Called from timer interrupt
void timer_tick() {
    static int counter = 0;
    if (++counter >= 10) {  // ~100ms
        counter = 0;
        asm volatile("int $0x20");  // trigger software interrupt for scheduling
    }
}