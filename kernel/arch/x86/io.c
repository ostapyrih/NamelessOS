#include "io.h"

uint16_t *fb = (uint16_t *) FRAMEBUFFER;
uint8_t row = 0;
uint8_t column = 0;
uint8_t color = 0;
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;

static inline uint8_t vga_entry_color(uint8_t fg, uint8_t bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(uint8_t uc, uint8_t color) 
{
	return (long) uc | (long) color << 8;
}

void set_color(uint8_t fg, uint8_t bg) {
    color = vga_entry_color(fg, bg);
}

void fb_write_char(int8_t c) {

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

void fb_write(int8_t *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        fb_write_char(str[i]);
    }
}

void fb_write_hex(uint32_t n)
{
    const char hex_lookup[] = "0123456789ABCDEF";
    const char *str[10];
    for (int i = 0; i < 10; i ++) {
        str[i] = '\0';
    }
    char i = 8;
    while (n != 0) {
        str[i] = hex_lookup[n % 16];
        n = n / 16;
        i--;
    }
    fb_write("0x");
    for (int i = 0; i < 10; i++) {
        if (str[i] != '\0')
            fb_write_char(str[i]);
    }
    fb_write_char('\n');
}

void fb_write_dec(uint32_t n)
{

}