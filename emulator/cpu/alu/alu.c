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

uint64_t checkSigned64(uint64_t number) {
    return number & ((uint64_t)1 << 63);
}

void computeAlu(ALU *alu) {
    alu->flags = 0;
    
    uint64_t inA = alu->inA;
    uint64_t inB = alu->inB;

    __uint128_t result = 0;
    uint64_t rest = 0;
    
    switch (alu->opcode) {

    case OP_ADD:
        result = (__uint128_t)inA + (__uint128_t)inB;   
        alu->out = (uint64_t)result;
        rest = (uint64_t)(result >> 64);

        if (alu->out == 0) alu->flags |= FLAG_Z;

        if (checkSigned64(alu->out)) alu->flags |= FLAG_N;

        if (alu->out < inA) alu->flags |= FLAG_C;

        if (rest > 0) alu->flags |= FLAG_V;

        break;

    case OP_SUB:
        result = (__uint128_t)inA - (__uint128_t)inB;     
        alu->out = (uint64_t)result;
        rest = (uint64_t)(result >> 64);

        if (alu->out == 0) alu->flags |= FLAG_Z;

        if (checkSigned64(alu->out)) alu->flags |= FLAG_N;

        if (inA < inB) {
            alu->flags |= FLAG_C;
            alu->flags |= FLAG_U;
        }

        if (rest > 0) alu->flags |= FLAG_V;

        break;    

    case OP_NEG:

        alu->out = ~inA +1;

        if (alu->out == 0) alu->flags |= FLAG_Z;

        if (checkSigned64(alu->out)) alu->flags |= FLAG_N;

        if (inA != 0) alu->flags |= FLAG_C;

        if (inA == INT64_MIN) alu->flags |= FLAG_V;
        
        break;  
        
    case OP_INC:

        alu->out = inA +1;

        if (alu->out == 0) alu->flags |= FLAG_Z;

        if (checkSigned64(alu->out)) alu->flags |= FLAG_N;

        if (inA == UINT64_MAX) {
            alu->flags |= FLAG_C;
            alu->flags |= FLAG_V;
        }

        break;

    case OP_DEC:
        alu->out = inA - 1;
    
        if (alu->out == 0) alu->flags |= FLAG_Z;

        if (checkSigned64(alu->out)) alu->flags |= FLAG_N;

        if (inA == 0) {
            alu->flags |= FLAG_C;
            alu->flags |= FLAG_U;
        }
    
        if (inA == INT64_MIN) alu->flags |= FLAG_V;
        
        break;

    case OP_MUL: {
        result = (__uint128_t)inA * (__uint128_t)inB;
        
        alu->out = (uint64_t)result;
        rest = (uint64_t)(result >> 64);
        
        if (alu->out == 0) alu->flags |= FLAG_Z;

        if (checkSigned64(alu->out)) alu->flags |= FLAG_N;
        
        if (rest > 0) {
            alu->flags |= FLAG_C;
            alu->flags |= FLAG_V;
        }
        
        break;        
    }
    
    default: 
        break;
    }
}