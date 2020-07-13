#include "memory.h"

uint32_t free_mem_addr = 0x10000;

void mem_cpy(uint8_t *source, uint8_t *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void mem_set(uint8_t *dest, uint8_t val, uint32_t len) {
    uint8_t *temp = (uint8_t *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

uint32_t malloc(uint32_t size) {
    uint32_t ret = free_mem_addr;
    free_mem_addr += size;
    return ret;
}