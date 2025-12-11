// In create_task, add ring 3 setup
void create_task(void (*entry)(), uint64_t pid, int user_mode) {
    // ... (previous code)
    if (user_mode) {
        t->regs.cs = 0x1B;  // User code segment (Ring 3)
        t->regs.ss = 0x23;  // User data segment (Ring 3)
        t->regs.rflags |= (1 << 12);  // IOPL=3 for user I/O
    }
    // ...
}

// Add fork implementation (simple)
long fork() {
    task_t* child = kmalloc(sizeof(task_t));
    if (!child) return -1;

    memcpy(child, current_task, sizeof(task_t));
    child->pid = next_pid++;
    child->regs.rax = 0;  // Child returns 0

    child->next = task_list;
    task_list = child;

    return child->pid;
}