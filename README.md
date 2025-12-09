# Neo-OS
Special Neo operating system
# Neo_OS — A Modern 64-bit Operating System from Scratch


A clean, educational, and fully bootable **64-bit operating system kernel** written in C and x86-64 assembly — built step by step with clarity, correctness, and future extensibility as the top priorities.

Neo_OS is designed for anyone who wants to truly understand how modern operating systems work at the lowest level, while keeping the code readable enough for teaching and hacking.

## Current Features (Fully Working Today)

| Feature                           | Status | Description                                                                      |
|-----------------------------------|--------|----------------------------------------------------------------------------------|
| GRUB multiboot boot               | Done   | Instant ISO boot in QEMU, VirtualBox, or real hardware                           |
| Full 16 → 32 → 64-bit transition  | Done   | Clean mode switches with GDT, paging, PAE, and long mode activation              |
| 64-bit Long Mode                  | Done   | Higher-half kernel at `0xFFFFFFFF80000000`                                       |
| 4-level paging (PML4→PDPT→PD→PT)  | Done   | Identity + recursive higher-half mapping                                         |
| Interrupt handling (IDT + PIC)    | Done   | Remapped PIC, keyboard IRQ1 fully functional                                     |
| PS/2 Keyboard driver              | Done   | Scancode → ASCII, backspace, line editing                                        |
| VGA Text Mode console             | Done   | Colored output, cursor tracking, simple `printf`-style printing                  |
| Interactive shell                 | Done   | Command prompt with built-in commands                                            |
| Built-in commands                 | Done   | `help`, `clear`, `hello`, `info`, `reboot`                                       |
| Modular & clean codebase          | Done   | Perfectly structured for GitHub and long-term development                        |

## Roadmap — The Future of Neo_OS

| Milestone                          | ETA         | Details                                                                 |
|------------------------------------|-------------|-------------------------------------------------------------------------|
| Physical & Virtual Memory Manager  | Next        | Buddy allocator, slab cache, demand paging, page faults                 |
| Preemptive Multitasking            | Next        | Processes, scheduler, context switching                                 |
| System Call Interface              | Next        | `syscall`/`sysret`, ring 3 user mode                                    |
| ELF Loader & User Programs         | Next        | Run separate binaries from kernel space                                 |
| Simple Filesystem (RAM disk → ext2)   | Next        | Persistent storage, `/bin`, `/dev`                                      |
| High-precision Timer (APIC)        | Next        | Sleep, preemption, timekeeping                                          |
| Heap (kmalloc/kfree)               | Next        | Dynamic kernel memory allocation                                        |
| SMP & Multi-core Support           | Next        | Boot and schedule across multiple CPU cores                             |
| Framebuffer Graphics (VBE/VESA)    | Next        | Move beyond text mode                                                   |
| Rust Safety-Critical Modules        | Next        | Optional safe drivers and core components in Rust                       |

Neo_OS will eventually become a modern, UNIX-like teaching kernel — think xv6, but 64-bit, clean, and actively maintained.

## Quick Start (Under 30 seconds)

```bash
git clone https://github.com/yourusername/Neo_OS.git
cd Neo_OS
make          # builds kernel + bootable os.iso
make run      # launch in QEMU (graphical window)
