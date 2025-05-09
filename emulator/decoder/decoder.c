#include "decoder.h"
#include "../opcodes.h"

#include <stdint.h>

void compute_decoder(
    uint64_t inputData, 
    uint8_t *funct3, 
    uint8_t *rd, 
    OPCODE *opcode
) {
    *opcode = inputData & 0b01111111;
    switch (*opcode) {
    // R-Type Layout:
    // [31-25] funct7
    // [24-20] rs2
    // [19-15] rs1
    // [14-12] funct3
    // [11-7]  rd
    // [6-0]   opcode
    case OP_ADD:
    case OP_SUB:
        *funct3 = (inputData >> 12) & 0b00000111;
        *rd = (inputData >> 7) & 0b00011111;
        break;

    // I-Type Layout:
    // [31-20] imm[11:0]
    // [19-15] rs1
    // [14-12] funct3
    // [11-7]  rd
    // [6-0]   opcode
    case OP_ADD:
    case OP_SUB:
        
        break;

    // S-Type Layout:
    // [31-25] imm[11:5]
    // [24-20] rs2
    // [19-15] rs1
    // [14-12] funct3
    // [11-7]  imm[4:0]
    // [6-0]   opcode
    case OP_ADD:
    case OP_SUB:
        
        break;

    // B-Type Layout:
    // [31]    imm[12]
    // [30-25] imm[10:5]
    // [24-20] rs2
    // [19-15] rs1
    // [14-12] funct3
    // [11-8]  imm[4:1]
    // [7]     imm[11]
    // [6-0]   opcode
    case OP_ADD:
    case OP_SUB:
        
        break;

    // U-Type Layout:
    // [31-12] imm[31:12]
    // [11-7]  rd
    // [6-0]   opcode
    case OP_ADD:
    case OP_SUB:
        
        break;

    // J-Type Layout:
    // [31]    imm[20]
    // [30-21] imm[10:1]
    // [20]    imm[11]
    // [19-12] imm[19:12]
    // [11-7]  rd
    // [6-0]   opcode
    case OP_ADD:
    case OP_SUB:
        
        break;
    
    default: break;
    }
}