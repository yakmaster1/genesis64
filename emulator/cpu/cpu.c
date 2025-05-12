#include "../seqgen/seqgen.h"
#include "../alu/alu.h"
#include "../decoder/decoder.h"
#include "../ddr/ddr.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define MEM_MAP 0x80000000

typedef struct RegFile RegFile;
typedef struct PipeReg PipeReg;

struct RegFile {
    uint64_t x0, x1, x2, x3, x4, x5, x6, x7, x8, x9;
    uint64_t x10, x11, x12, x13, x14, x15, x16, x17, x18, x19;
    uint64_t x20, x21, x22, x23, x24, x25, x26, x27, x28, x29;
    uint64_t x30, x31;
};

struct PipeReg {
    uint64_t intA;
    uint64_t intB;
}

void inputPipeRegister(PipeReg *reg, uint64_t value) {
    reg->intB = reg->intA;
    reg->intA = value;
}

int main() {
    RegFile *regFile = calloc(1, sizeof(RegFile));
    DIMM *dimm = calloc(1, sizeof(DIMM));
    Seqgen seq = get_seqgen();

    uint32_t pc = 0;

    PipeReg *pipeReg = calloc(4, sizeof(PipeReg));

    uint64_t *dataBus = calloc(4, sizeof(uint64_t));

    // testing
    uint64_t test = 0b10110011;
    ram_access(dimm, pc, 1, &test);
    
    for (size_t i = 0; i < 50; i++)
    {
        int c = i % 2;
        
        Seqphase phase = phase_seqgen(&seq);
        if (c) {
            if (phase == SEQPH_IF) {
                ram_access(dimm, pc, 0, &dataBus[0]);
            }
            if (phase == SEQPH_ID) {
                
            }
            if (phase == SEQPH_EX) {
                
            }
            if (phase == SEQPH_MEM) {
                
            }
            if (phase == SEQPH_WB) {
                
            }            
        }
    }

    free(regFile);
    free(dimm);
}