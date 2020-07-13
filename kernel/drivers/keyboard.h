#pragma once
#include "../core/stdlib.h"
#include "../arch/x86/io.h"

#define KBD_DATA_PORT   0x60
#define KB_STATUS_PORT  0x64

void keyboard_callback();