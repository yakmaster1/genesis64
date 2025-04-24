#include "alu/alu.h"

#include <stdio.h>

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
    ALU *alu = init_alu();

    alu_setInA(alu, (uint64_t)5);
    alu_setInB(alu, (uint64_t)7);
    alu_setOpcode(alu, OP_SUB);

    printBits64(alu->out);
    printBits8(alu->flags);

    dispose_alu(alu);
}