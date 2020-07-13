#pragma once

#include "stdlib.h"

void free(uint32_t *ptr);

void mem_cpy(uint8_t *source, uint8_t *dest, int nbytes);

void mem_set(uint8_t *dest, uint8_t val, uint32_t len);

uint32_t malloc(uint32_t size);