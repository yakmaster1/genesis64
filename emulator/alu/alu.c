#include "alu.h"
#include "../adder/adder.h"

#include <stdlib.h>
#include <stdio.h>

void computeAlu(uint64_t inA, uint64_t inB, uint8_t opcode, uint64_t *out) {
    bool cout = 0;
    uint64_t invertedB = inB ^ UINT64_MAX;
    uint64_t shamt = inB & 0b00111111;
    
    switch (alu->opcode) {
        // AU
        case ALU_ADD:
            full_adder64(inA, inB, 0, out, &cout);
            break;            
        case ALU_SUB: 
            full_adder64(inA, invertedB, 1, out, &cout);
            break;  

        // LU
        case ALU_AND:
            *out = inA & inB;
            break;           
        case ALU_OR:
            *out = inA | inB;
            break;       
        case ALU_XOR:
            *out = inA ^ inB;
            break;  

        // SU (Barrel Shifter)
        case ALU_SLL: 
            *out = (inA << shamt);
            break;
        case ALU_SRL: 
            *out = (inA >> shamt);
            break;
        case ALU_SRA: {
            uint64_t shifted = (inA >> shamt);
            if ((inA >> 63) & 0b1 && shamt != 0) shifted |= (uint64_t)(UINT64_MAX << (64 - shamt));
            *out = shifted;
            break;            
        }

        case ALU_SLT:
            alu->out = ((int64_t)inA < (int64_t)inB) ? 1 : 0;
            break;
        case ALU_SLTU:
            alu->out = (inA < inB) ? 1 : 0;
            break; 

        default: break;
    }
}

int main(int argc, char const *argv[])
{
    printf("%d", FLAG_Z);
    return 0;
}
