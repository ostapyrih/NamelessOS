#pragma once
#include "../../core/stdlib.h"

#define FRAMEBUFFER 0x000B8000

void set_color(uint8_t fg, uint8_t bg);
void fb_write_char(int8_t c);
void fb_write(int8_t *str);
void fb_write_hex(uint32_t n);

unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char data);