#include "alu.h"
#include "adder.h"

#include <stdlib.h>

void computeAlu(ALU *alu);

ALU *init_alu() {
    ALU *alu = malloc(sizeof(ALU));
    alu->inA = 0;
    alu->inB = 0;
    alu->opcode = 0;

    alu->out = 0;
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
    if (!alu) return;
    
    uint64_t inA = alu->inA;
    uint64_t inB = alu->inB;

    uint64_t out = 0;
    bool cout = 0;

    //uint64_t shamt = inB & 0b00111111;
    
    switch (alu->opcode) {
        case ALU_ADD: {
            full_adder64(inA, inB, 0, &out, &cout);
            alu->out = out;
            break;            
        }
        case ALU_SUB: {
            uint64_t invertedB = inB ^ UINT64_MAX;
            full_adder64(inA, invertedB, 1, &out, &cout);
            alu->out = out;
            break;  
        }  
    
/*     case ALU_AND:
        alu->out = inA & inB;
        break;           

    case ALU_OR:
        alu->out = inA | inB;
        break;       

    case ALU_XOR:
        alu->out = inA ^ inB;
        break; 

    case ALU_SLL: 
        alu->out = (inA << shamt);
        break;

    case ALU_SRL: 
        alu->out = (inA >> shamt);
        break;

    case ALU_SRA: 
        uint64_t shifted = (inA >> shamt);
        if ((inA >> 63) & 0b1 && shamt != 0) shifted |= (uint64_t)(UINT64_MAX << (64 - shamt));
        alu->out = shifted;
        break;

    case ALU_SLT:
        alu->out = ((int64_t)inA < (int64_t)inB) ? 1 : 0;
        break;

    case ALU_SLTU:
        alu->out = (inA < inB) ? 1 : 0;
        break; */

    default: 
        break;
    }
}