#include "alu.h"
#include "../adder/adder.h"
#include "../bshifter/bshifter.h"

enum ALU_OP {
    ALU_ADD, ALU_SUB,
    ALU_AND, ALU_OR, ALU_XOR,
    ALU_SLL, ALU_SRL, ALU_SRA,
    ALU_SLT, ALU_SLTU
};

void computeAlu(uint64_t inA, uint64_t inB, ALU_OP opcode, uint64_t *out) {
    bool cout = 0;
    uint64_t invertedB = inB ^ UINT64_MAX;
    uint8_t shamt = inB & 0b00111111;
    
    switch (opcode) {
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

        // SU
        case ALU_SLL: 
            bshift64(inA, shamt, 0, 1, out);
            break;
        case ALU_SRL: 
            bshift64(inA, shamt, 1, 0, out);
            break;
        case ALU_SRA: 
            bshift64(inA, shamt, 1, 1, out);
            break;    
        
        case ALU_SLT: {
            uint64_t sum = 0;
            full_adder64(inA, invertedB, 1, &sum, &cout);
            *out = (uint64_t)((sum >> 63) & 1);
        }
        case ALU_SLTU: {
            uint64_t _ = 0;
            full_adder64(inA, invertedB, 1, &_, &cout);
            *out = (uint64_t)(!cout & 1);
        }

        default: break;
    }
}