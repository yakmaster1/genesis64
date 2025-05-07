#include "bshifter.h"

void mux2_1(bool a, bool b, bool s, bool *out) {
    *out = 0;
    *out = (
        (a & (!s)) | 
        (b &   s )
    );
}

void mux4_1(bool a, bool b, bool c, bool d, bool s1, bool s0, bool *out) {
    *out = 0;
    bool bit_mux1out, bit_mux2out;

    mux2_1(a, b, s0, &bit_mux1out);
    mux2_1(c, d, s0, &bit_mux2out);

    mux2_1(bit_mux1out, bit_mux2out, s1, out);
}

void shift64(uint64_t in, bool s1, bool s0, uint64_t *out, int shamt) {
    if (shamt <= 0 || shamt > 64) return;
    *out = 0;

    bool bit_a, bit_b, bit_c, bit_d, bit_out;
    for (int i = 0; i < 64; i++)
    {
        bit_a = (in >> i) & 1;
        bit_b = 0;
        bit_c = 0;
        bit_d = 0;
        bit_out = 0;
        
        if (i - shamt >= 0) bit_b = (in >> (i-shamt)) & 1; // SLL
        if (i + shamt < 64) bit_c = (in >> (i+shamt)) & 1; // SRL
        
        // SRA
        if (i + shamt < 64) {
            bit_d = (in >> (i+shamt)) & 1;
        } else {
            bit_d = (in >> 63) & 1;
        }

        mux4_1(bit_a, bit_b, bit_c, bit_d, s1, s0, &bit_out);

        *out |= (uint64_t)(bit_out << i);
    }
}

void bshift64(uint64_t in, uint8_t shamt, bool s1, bool s0, uint64_t *out) {
    *out = 0;
    uint8_t masked = (shamt & 0b00111111);

    uint64_t stage0, stage1, stage2, stage3, stage4, stage5;
    shift64(    in, (s1 & ((masked >> 0) & 1)), (s0 & ((masked >> 0) & 1)), &stage0,  1);
    shift64(stage0, (s1 & ((masked >> 1) & 1)), (s0 & ((masked >> 1) & 1)), &stage1,  2);
    shift64(stage1, (s1 & ((masked >> 2) & 1)), (s0 & ((masked >> 2) & 1)), &stage2,  4);
    shift64(stage2, (s1 & ((masked >> 3) & 1)), (s0 & ((masked >> 3) & 1)), &stage3,  8);
    shift64(stage3, (s1 & ((masked >> 4) & 1)), (s0 & ((masked >> 4) & 1)), &stage4, 16);
    shift64(stage4, (s1 & ((masked >> 5) & 1)), (s0 & ((masked >> 5) & 1)), &stage5, 32);
    *out = stage5;
}

