#ifndef ADDER_H
#define ADDER_H

#include <stdbool.h>
#include <stdint.h>

void full_adder64(uint64_t a, uint64_t b, bool cin, uint64_t *s, bool *cout);

#endif