#include "../lib/stdlib.h"

uint8_t cursor_x;
uint8_t cursor_y;

void outb(unsigned short port, unsigned char data);

unsigned char inb(unsigned short port);

void update_cursor(int x, int y);

void fb_write_char(char c);

void fb_write(char *c);

void set_color(uint8_t fg, uint8_t bg);

void putpixel(unsigned char* screen, int x,int y, int color);

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);