// neo_os_runner.c
// One-click launcher for the real Neo OS kernel
// Compile: gcc neo_os_runner.c -o neo_os_runner -lSDL2
// Windows (MinGW): gcc neo_os_runner.c -o neo_os_runner.exe -lmingw32 -lSDL2main -lSDL2

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define ISO_PATH "os.iso"           // Must be built with 'make' first

int main(int argc, char* argv[]) {
    // Check if the bootable ISO exists
    FILE* iso_file = fopen(ISO_PATH, "rb");
    if (!iso_file) {
        printf("Error: '%s' not found!\n", ISO_PATH);
        printf("Please run 'make' in the Neo_OS directory first to build the ISO.\n");
        printf("Press Enter to exit...\n");
        getchar();
        return 1;
    }
    fclose(iso_file);

    // Build QEMU command with SDL window output
    char command[2048];
    snprintf(command, sizeof(command),
        "qemu-system-x86_64 "
        "-cdrom %s "
        "-m 512M "
        "-vga std "
        "-display sdl "           // Opens a native window
        "-serial stdio "          // Shell output goes to your terminal
        "-no-reboot "
        "-d cpu_reset,int "       // Optional: debug info (remove if too verbose)
        "-sdl",
        ISO_PATH
    );

    printf("=====================================\n");
    printf("   Neo OS v1.0 - Real Kernel Launch\n");
    printf("   Author: Nima Mokhtari\n");
    printf("=====================================\n");
    printf("Starting the real 64-bit kernel in a window...\n");
    printf("Close the window or press Ctrl+C to exit.\n\n");

    // Launch the real kernel using QEMU + SDL
    int result = system(command);

    if (result != 0) {
        printf("\nQEMU failed. Make sure it is installed:\n");
        printf("  Linux/WSL: sudo apt install qemu-system-x86\n");
        printf("  macOS:     brew install qemu\n");
        printf("  Windows:   Download from https://www.qemu.org/download/\n");
    }

    return 0;
}