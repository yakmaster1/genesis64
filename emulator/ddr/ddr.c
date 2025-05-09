#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define BITLINES 512
#define WORDLINES 2048

typedef struct Memcell8 Memcell8;
typedef struct RamTile RamTile;
typedef struct RamBank RamBank;
typedef struct RamChip RamChip;
typedef struct DIMM DIMM;
typedef struct RamModule RamModule;

struct Memcell8
{
    uint8_t value;
};

struct RamBank 
{
    Memcell8 cellblock[WORDLINES/8][BITLINES];
    uint64_t bitlineBits64[BITLINES/64];
    uint16_t activeWordline;
};

struct RamChip 
{
    RamBank bank[32];
};

struct DIMM
{
    RamChip chip[8];
};

struct RamModule
{
    DIMM dimm[4];
};

void setBitlines(RamBank *bank, 
    uint64_t b0, uint64_t b1, 
    uint64_t b2, uint64_t b3, 
    uint64_t b4, uint64_t b5,
    uint64_t b6, uint64_t b7,
) {
    bank->bitlineBits64[0] = b0;
    bank->bitlineBits64[1] = b1;
    bank->bitlineBits64[2] = b2;
    bank->bitlineBits64[3] = b3;
    bank->bitlineBits64[4] = b4;
    bank->bitlineBits64[5] = b5;
    bank->bitlineBits64[6] = b6;
    bank->bitlineBits64[7] = b7;
}

void prechargeBitlines(RamBank *bank) {
    for (int i = 0; i < BITLINES/64; i++)
    {
        bank->bitlineBits64[i] = 0;
    }
}

bool getBitFromBank(RamBank *bank, uint16_t row, uint16_t col) {
    uint16_t colMasked = col & 0b111111111;
    uint16_t rowMasked = row & 0b11111111111;

    int group = rowMasked / 8;
    int bit = rowMasked % 8;

    return (bank->cellblock[group][colMasked].value >> bit) & 1;
}

void setWordline(RamBank *bank, uint16_t row) {
    bank->activeWordline = row & 0b11111111111;
    
}

int main(int argc, char const *argv[])
{


    return 0;
}
