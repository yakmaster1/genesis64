#ifndef ALU_H
#define ALU_H

#include <stdint.h>

#define FLAG_Z (1 << 0)
#define FLAG_N (1 << 1)
#define FLAG_C (1 << 2)
#define FLAG_V (1 << 3)
#define FLAG_NAN (1 << 4)
#define FLAG_INF (1 << 5)
#define FLAG_U (1 << 6)

#define OP_ADD 0
#define OP_SUB 1
#define OP_NEG 2
#define OP_INC 3
#define OP_DEC 4
#define OP_MUL 5

typedef struct ALU ALU;

struct ALU {
    uint64_t inA;
    uint64_t inB;
    uint8_t opcode;

    uint64_t out;
    uint8_t flags;
};

ALU *init_alu();
void dispose_alu(ALU *alu);
void alu_setInA(ALU *alu, uint64_t value);
void alu_setInB(ALU *alu, uint64_t value);
void alu_setOpcode(ALU *alu, uint8_t value);

#endif