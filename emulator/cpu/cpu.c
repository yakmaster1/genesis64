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
    uint64_t in;
    uint64_t out;
};

void save_pipereg(PipeReg *reg, uint64_t value) {
    reg->out = reg->in;
    reg->in = value;
}

int main() {
    RegFile *regFile = calloc(1, sizeof(RegFile));
    DIMM *dimm = calloc(1, sizeof(DIMM));
    Seqgen seq = get_seqgen();

    uint32_t pc = 0;

    PipeReg *pipeReg = calloc(5, sizeof(PipeReg));

    uint64_t *dataBus = calloc(5, sizeof(uint64_t));

    // testing
    uint64_t test = (uint64_t)0 | 5;
    ram_access(dimm, pc, true, &test);

    test = (uint64_t)0 | 7;
    ram_access(dimm, pc+1, true, &test);
    
    for (size_t i = 0; i < 5; i++)
    {
    // C1

        // FETCH
        ram_access(dimm, pc, false, &(dataBus[0]));

        // DECODE
        uint16_t imm = 0;
        uint8_t funct7 = 0;
        uint8_t rs2 = 0;
        uint8_t rs1 = 0;
        uint8_t funct3 = 0;
        uint8_t rd = 0;
        uint8_t opcode = 0;        
        compute_decoder(pipeReg[0].out, &imm, &funct7, &rs2, &rs1, &funct3, &rd, &opcode);

        printf("%d\n", opcode);

    // C2
            
        // FETCH
        save_pipereg(&(pipeReg[0]), dataBus[0]);
        pc++;
         
    }

    free(regFile);
    free(dimm);
}