#ifndef BSHIFTER_H
#define BSHIFTER_H

#include <stdbool.h>
#include <stdint.h>

void bshift64(uint64_t in, uint8_t shamt, bool s1, bool s0, uint64_t *out);

#endif
