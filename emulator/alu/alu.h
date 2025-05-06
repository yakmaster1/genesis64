#ifndef ALU_H
#define ALU_H

#include <stdint.h>

typedef struct ALU ALU;
typedef enum ALU_OP ALU_OP;

enum ALU_OP {
    ALU_ADD, ALU_SUB,
    ALU_AND, ALU_OR, ALU_XOR,
    //ALU_SLL, ALU_SRL, ALU_SRA,
    //ALU_SLT, ALU_SLTU
};

struct ALU {
    uint64_t inA;
    uint64_t inB;
    uint8_t opcode;

    uint64_t out;
};

ALU *init_alu();
void dispose_alu(ALU *alu);
void alu_setInA(ALU *alu, uint64_t value);
void alu_setInB(ALU *alu, uint64_t value);
void alu_setOpcode(ALU *alu, uint8_t value);

#endif