#include "cpu.h"

#include "../seqgen/seqgen.h"
#include "../alu/alu.h"
#include "../decoder/decoder.h"

#include <stdio.h>
#include <stdint.h>

void printBits8(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

void printBits64(uint64_t value) {
    for (int i = 63; i >= 0; i--) {
        //printf("%d", (value >> i) & 1);
        if (i % 8 == 0 && i != 0) printf(" ");
    }
    printf("\n");
}

int main() {
    CPU cpu = {0};
    ALU alu = {0};
    Decoder dec = {0};
    
    Seqgen seq = get_seqgen();

    for (size_t i = 0; i < 50; i++)
    {

    }
}