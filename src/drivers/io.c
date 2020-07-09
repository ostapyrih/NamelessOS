#include "io.h"

#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

uint16_t *fb = (uint16_t *) 0x000B8000;
uint8_t row = 0;
uint8_t column = 0;
uint8_t color = 0;
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;

static inline uint8_t vga_entry_color(uint8_t fg, uint8_t bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (long) uc | (long) color << 8;
}

void set_color(uint8_t fg, uint8_t bg) {
    color = vga_entry_color(fg, bg);
}

void fb_write_char(char c) {

    if (c == '\n') {
        row++;
        column = 0;
    } else if (c == '\b') {
        if (column == 0) {
            column = 79;
            row--;
        } else {
            column--;
        }
        fb[column + row * 80] = vga_entry('\0', color);
    } else {    
        fb[column + row * 80] = vga_entry(c, color);
        column++;
    }

    if (column > 80) {
        row++;
        column = 0;
    }
    //fb_move_cursor(column + row * 80);
}

void fb_write(char* c) {

    for (uint8_t i=0; i < strlen(c); i++) {
        fb_write_char(c[i]);
    }

}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);

    update_cursor(cursor_x, cursor_y);
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * 80 + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}