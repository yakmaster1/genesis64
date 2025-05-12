#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>

void compute_decoder(
    uint64_t inputData, 
    uint16_t *imm,
    uint8_t *funct7,
    uint8_t *rs2,
    uint8_t *rs1,
    uint8_t *funct3, 
    uint8_t *rd, 
    uint8_t *opcode
);

#endif