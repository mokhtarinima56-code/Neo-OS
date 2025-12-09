; kernel/paging.asm - Identity map first 4GB + higher half kernel
[bits 32]
global enable_paging

section .bss
align 4096
p4_table: resb 4096
p3_table: resb 4096
p2_table: resb 4096
p1_table: resb 4096

section .text
enable_paging:
    ; Clear tables
    mov edi, p4_table
    mov ecx, 4096*4 / 4
    xor eax, eax
    rep stosd

    ; P4[0] → P3
    mov eax, p3_table
    or eax, 0x3               ; Present + Writable
    mov [p4_table], eax

    ; P3[0] → P2
    mov eax, p2_table
    or eax, 0x3
    mov [p3_table], eax

    ; P2[0..511] → 2MB pages (identity map 0–1GB)
    mov eax, 0x83             ; Present + Writable + Huge (2MB)
    mov ebx, p2_table
    mov ecx, 512
.map_p2:
    mov [ebx], eax
    add eax, 0x200000
    add ebx, 8
    loop .map_p2

    ; Higher half mapping: map 0x100000 → 0xFFFFFFFF80000000
    mov eax, p3_table + 4096 - 8
    mov ebx, p2_table
    or ebx, 0x3
    mov [eax], ebx            ; P3[511] → P2 (for higher half)

    ; Enable PAE + PGE
    mov eax, cr4
    or eax, (1 << 5) | (1 << 7)
    mov cr4, eax

    ; Set Long Mode bit in EFER
    mov ecx, 0xC0000080
    rdmsr
    or eax, (1 << 8)
    wrmsr

    ; Load CR3
    mov eax, p4_table
    mov cr3, eax

    ; Enable paging
    mov eax, cr0
    or eax, (1 << 31) | (1 << 0)
    mov cr0, eax

    ret