#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void mux1bit(bool a, bool b, bool s, bool *out) {
    *out = (
        (a & (!s)) | 
        (b &   s )
    );
}

void shift64(uint64_t in, bool shift, uint64_t *out, int m, bool mode) {
    if (m < 1) return;

    *out = 0;
    
    bool bit_a, bit_b, bit_out;
    for (int i = 0; i < 64; i++)
    {
        bit_a = (in >> i) & 1;
        
        bit_b = 0;
        if (mode) {
            if (i + m < 64) bit_b = (in >> (i + m)) & 1;
        } else {
            if (i >= m) bit_b = (in >> (i - m)) & 1;
        }

        mux1bit(bit_a, bit_b, shift, &bit_out);

        *out |= (uint64_t)(bit_out << i);
    }
}
