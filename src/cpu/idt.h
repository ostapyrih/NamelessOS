#include "../lib/stdlib.h"

struct IDT_entry{
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
};
 
struct IDT_entry IDT[256];

void interrupt_handler(void);
void interrupt_handler2(void);

void idt_init();