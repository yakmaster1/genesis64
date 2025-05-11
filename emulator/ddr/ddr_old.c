#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// RAS = 11 bits wl sel + 5 bits bank sel = 16 bits

// 512/8 => 64 select MUX Column -> 6 bits
#define BITLINES 512
#define BL_MASK 0b111111111
// 11 Bits Wordline select
#define WORDLINES 2048
#define WL_MASK 0b11111111111

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
};

// 5 Bits bank select
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
    uint64_t b7, uint64_t b6, 
    uint64_t b5, uint64_t b4, 
    uint64_t b3, uint64_t b2,
    uint64_t b1, uint64_t b0
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

bool _getBitFromBank(RamBank *bank, uint16_t row, uint16_t col) {
    uint16_t colMasked = BL_MASK - (col & BL_MASK);
    uint16_t rowMasked = row & WL_MASK;

    int group = rowMasked / 8;
    int bit = 7 - (rowMasked % 8);

    return (bank->cellblock[group][colMasked].value >> bit) & 1;
}

void _setBitToBank(RamBank *bank, uint16_t row, uint16_t col) {
    uint16_t colMasked = BL_MASK - (col & BL_MASK);
    uint16_t rowMasked = row & WL_MASK;

    int group = rowMasked / 8;
    int bit = 7 - (rowMasked % 8);

    bank->cellblock[group][colMasked].value |= (uint8_t)(1 << bit);
}

void columnMuxRam_writeToBitline(RamBank *bank, uint8_t cas, uint8_t value) {
    uint8_t casMasked = cas & 0b111111;

    int casBitPosition = casMasked * 8;

    int bitlineGroup = casBitPosition / 64;
    int offsetLeft = casBitPosition % 64;
    int offsetRight = 64 - 8 - offsetLeft;

    uint64_t overwrite = (uint64_t)(value << offsetRight);
    printf("%d\n", overwrite);

    bank->bitlineBits64[7 - bitlineGroup] |= overwrite;
};

uint8_t columnMuxRam_readFromBitline(RamBank *bank, uint8_t cas) {
    uint8_t casMasked = cas & 0b111111;

    int casBitPosition = casMasked * 8;

    int bitlineGroup = casBitPosition / 64;
    int offsetLeft = casBitPosition % 64;
    int offsetRight = 64 - 8 - offsetLeft;

    uint64_t groupBits = bank->bitlineBits64[7 - bitlineGroup];
    return (uint8_t)(groupBits >> offsetRight);
}

void setWordlineImpulse(RamBank *bank, uint16_t row) {
    uint16_t rowMasked = row & WL_MASK;
    for (size_t i = 0; i < BITLINES; i++)
    {
        int bitlineGroup = i / 64;
        int offset = i % 64;
        bool bankBit = _getBitFromBank(bank, rowMasked, i);
        bool bitlineBit = (bank->bitlineBits64[7 - bitlineGroup] >> offset) & 1;

        if (bitlineBit != bankBit) {
            if (bankBit) {
                bank->bitlineBits64[7 - bitlineGroup] |= (uint64_t)(bankBit << offset);
            } else {
                _setBitToBank(bank, rowMasked, i);
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    RamBank bank = {0};

    prechargeBitlines(&bank);

    columnMuxRam_writeToBitline(&bank, 0, 3);
    printf("%d\n", bank.bitlineBits64[7]);
    setWordlineImpulse(&bank, 0);

    prechargeBitlines(&bank);

    setWordlineImpulse(&bank, 0);
    uint8_t value = columnMuxRam_readFromBitline(&bank, 0);


    printf("%d\n", value);

    

    return 0;
}
