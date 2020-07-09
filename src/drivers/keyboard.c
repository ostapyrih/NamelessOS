#include "keyboard.h"
#include "../lib/strings.h"
#include "../lib/stdlib.h"
#include "io.h"

const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};


void handle_keyboard() {

	uint8_t scancode = inb(0x60);

    char letter;

    switch (scancode)
    {
    case 0x1c: // Enter
        fb_write_char('\n');
        break;
    case 0x0e: // Backspace
        fb_write_char('\b');
        break;
    case 0x48: // Up Arrow
        update_cursor(cursor_x, --cursor_y);
        break;
    case 0x50: // Down Arrow
        update_cursor(cursor_x, ++cursor_y);
        break;
    case 0x4b: // Left arrow
        update_cursor(--cursor_x, cursor_y);
        break;
    case 0x4d: // Right arrow
        update_cursor(++cursor_x, cursor_y);
        break;
    default:
        if (scancode < 57) {
            letter = sc_ascii[(int)scancode];
            fb_write_char(letter);
        }
    }
}