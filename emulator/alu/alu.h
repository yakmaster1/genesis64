#ifndef ALU_H
#define ALU_H

#include <stdint.h>

typedef enum ALU_OP ALU_OP;

void computeAlu(uint64_t inA, uint64_t inB, ALU_OP opcode, uint64_t *out);

#endif