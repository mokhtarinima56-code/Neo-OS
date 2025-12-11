// kernel/syscall.h - System call interface for user mode

#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

#define SYS_EXIT  1
#define SYS_FORK  2
#define SYS_EXEC  3
#define SYS_WRITE 4

long syscall(long number, ...);

#endif