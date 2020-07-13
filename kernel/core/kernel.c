#include "../arch/x86/io.h"
#include "../arch/x86/gdt.h"
#include "../arch/x86/idt.h"
#include "../arch/x86/isr.h"
#include "memory.h"

void kmain() {
    set_color(15, 0);
    fb_write("Initializing global descriptor table...\n");
    gdt_install();
    fb_write("Initializing interrupt Service Routine...\n");
    isr_install();
    fb_write("Initializing interrupts descriptor table...\n");
    idt_init();
    fb_write("Nameless OS loaded!\n");
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}