#include "alu.h"

#include <stdlib.h>

void computeAlu(ALU *alu);

ALU *init_alu() {
    ALU *alu = malloc(sizeof(ALU));
    alu->inA = 0;
    alu->inB = 0;
    alu->opcode = 0;

    alu->out = 0;
    alu->flags = 0;
    return alu;
}

void dispose_alu(ALU *alu) {
    if (alu) free(alu);
}

void alu_setInA(ALU *alu, uint64_t value) {
    alu->inA = value;
    computeAlu(alu);
}

void alu_setInB(ALU *alu, uint64_t value) {
    alu->inB = value;
    computeAlu(alu);
}

void alu_setOpcode(ALU *alu, uint8_t value) {
    alu->opcode = value;
    computeAlu(alu);
}

void computeAlu(ALU *alu) {
    alu->flags = 0;
    
    int64_t a = (int64_t)alu->inA;
    int64_t b = (int64_t)alu->inB;
    int64_t r = 0;
    
    switch (alu->opcode) {

    case OP_ADD:
        
        alu->out = alu->inA + alu->inB;
        r = (int64_t)alu->out;

        if (alu->out == 0) alu->flags |= FLAG_Z;

        if ((int64_t)alu->out < 0) alu->flags |= FLAG_N;

        if (alu->out < alu->inA) alu->flags |= FLAG_C;

        if ((a > 0 && b > 0 && r < 0) || (a < 0 && b < 0 && r > 0)) {
            alu->flags |= FLAG_V;
        }

        break;

    case OP_SUB:

        alu->out = alu->inA - alu->inB;
        r = (int64_t)alu->out;

        if (alu->out == 0) alu->flags |= FLAG_Z;

        if ((int64_t)alu->out < 0) alu->flags |= FLAG_N;

        if (alu->inA < alu->inB) {
            alu->flags |= FLAG_C;
            alu->flags |= FLAG_U;
        }

        if ((a > 0 && b < 0 && r < 0) || (a < 0 && b > 0 && r > 0)) {
            alu->flags |= FLAG_V;
        }
        
        break;    

    case OP_NEG:

        alu->out = ~alu->inA + 1;
        r = (int64_t)alu->out;

        if (alu->out == 0) alu->flags |= FLAG_Z;

        if (r < 0) alu->flags |= FLAG_N;

        if (alu->inA != 0) alu->flags |= FLAG_C;

        if (a == INT64_MIN) alu->flags |= FLAG_V;
        
        break;   
    
    default: break;
    }
}