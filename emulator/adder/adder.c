#include "adder.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

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
    bool bit_a, bit_b;

    bool bit_cin = cin;

    for (size_t i = 0; i < 64; i++)
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

int main(int argc, char const *argv[])
{
    uint64_t a = 44;
    uint64_t b = 1;
    bool cin = 0;

    uint64_t s = 0;
    bool cout = 0;
    full_adder64(a, b, cin, &s, &cout);

    printf("%d", s);
    return 0;
}
