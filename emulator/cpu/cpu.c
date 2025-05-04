#include "cpu.h"

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
    for (size_t i = 0; i < 500; i++)
    {
        uint8_t clock = i % 2;
        printf("%d", clock); 
    }
}