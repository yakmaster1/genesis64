#ifndef ALU_H
#define ALU_H

#include <stdint.h>

typedef enum ALU_OP {
    ALU_ADD, ALU_SUB,
    ALU_AND, ALU_OR, ALU_XOR,
    ALU_SLL, ALU_SRL, ALU_SRA,
    ALU_SLT, ALU_SLTU
};

void computeAlu(uint64_t inA, uint64_t inB, uint8_t opcode, uint64_t *out);

#endif