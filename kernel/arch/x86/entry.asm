global start
global gdt_flush

MBOOT_ALIGN       equ 1<<0
MBOOT_MEMINFO     equ 1<<1
MBOOT_FLAGS       equ MBOOT_ALIGN | MBOOT_MEMINFO
MBOOT_MAGIC       equ 0x1BADB002
MBOOT_CHECKSUM    equ -(MBOOT_MAGIC + MBOOT_FLAGS)

section .multiboot
    align 4
    dd MBOOT_MAGIC
    dd MBOOT_FLAGS
    dd MBOOT_CHECKSUM

section .bss
    align 16
    stack_bottom:
    resb 16384
    stack_top:

section .text
extern gp
gdt_flush:
    lgdt [gp]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2
flush2:
    ret
    
start:
    mov esp, stack_top
    extern kmain
    call kmain

.hang:
    jmp .hang