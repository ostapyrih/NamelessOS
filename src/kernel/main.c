#include "../drivers/io.h"
#include "../lib/mem.h"
#include "../lib/stdlib.h"
#include "../cpu/idt.h"

void kernel_virtual_start(void);
void kernel_virtual_end(void);
void kernel_physical_start(void);
void kernel_physical_end(void);

int main() {
    set_color(0, 15);
    idt_init();
    
    free_mem_addr = (uint32_t) &kernel_physical_start;

}