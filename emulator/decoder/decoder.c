#include "decoder.h"

#include "../opcodes.h"
#include <stdio.h>

void compute_decoder(
    uint64_t inputData, 
    uint16_t *imm,
    uint8_t *funct7,
    uint8_t *rs2,
    uint8_t *rs1,
    uint8_t *funct3, 
    uint8_t *rd, 
    uint8_t *opcode
) {
    *imm = 0;
    *funct7 = 0;
    *rs2 = 0;
    *rs1 = 0;
    *funct3 = 0;
    *rd = 0;
    *opcode = 0;
    
    *opcode = inputData & 0b01111111;
    switch (*opcode) {
    // R-Type Layout:
    // [31-25] funct7
    // [24-20] rs2
    // [19-15] rs1
    // [14-12] funct3
    // [11-7]  rd
    // [6-0]   opcode
    case (uint8_t)OP_ADD:
    case (uint8_t)OP_SUB: 
        *funct7 = (inputData >> 25) & 0b1111111;
        *rs2 = (inputData >> 20) & 0b11111;
        *rs1 = (inputData >> 15) & 0b11111;
        *funct3 = (inputData >> 12) & 0b111;
        *rd = (inputData >> 7) & 0b11111;
        break;

    // I-Type Layout:
    // [31-20] imm[11:0]
    // [19-15] rs1
    // [14-12] funct3
    // [11-7]  rd
    // [6-0]   opcode

    // S-Type Layout:
    // [31-25] imm[11:5]
    // [24-20] rs2
    // [19-15] rs1
    // [14-12] funct3
    // [11-7]  imm[4:0]
    // [6-0]   opcode


    // B-Type Layout:
    // [31]    imm[12]
    // [30-25] imm[10:5]
    // [24-20] rs2
    // [19-15] rs1
    // [14-12] funct3
    // [11-8]  imm[4:1]
    // [7]     imm[11]
    // [6-0]   opcode


    // U-Type Layout:
    // [31-12] imm[31:12]
    // [11-7]  rd
    // [6-0]   opcode


    // J-Type Layout:
    // [31]    imm[20]
    // [30-21] imm[10:1]
    // [20]    imm[11]
    // [19-12] imm[19:12]
    // [11-7]  rd
    // [6-0]   opcode
    
    default: break;
    }
}