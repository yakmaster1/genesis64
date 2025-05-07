#include "adder.h"

void half_adder(bool a, bool b, bool *s, bool *c) {
    *s = a ^ b;
    *c = a & b;
}

void full_adder(bool a, bool b, bool cin, bool *s, bool *cout) {
    bool s1, s2, cout1, cout2;

    half_adder(a, b, &s1, &cout1);
    half_adder(s1, cin, &s2, &cout2);

    *cout = cout1 | cout2;
    *s = s2;
}

void full_adder64(uint64_t a, uint64_t b, bool cin, uint64_t *s, bool *cout) {
    bool bit_a, bit_b, bit_cin;

    bit_cin = cin;

    for (int i = 0; i < 64; i++)
    {
        bool bit_a = (a >> i) & 1;
        bool bit_b = (b >> i) & 1;
        bool bit_s, bit_cout;

        full_adder(bit_a, bit_b, bit_cin, &bit_s, &bit_cout);

        *s |= (bit_s << i);

        bit_cin = bit_cout;
    }
    *cout = bit_cin;
}
