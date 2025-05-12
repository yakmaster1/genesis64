#ifndef DDR_H
#define DDR_H

#include <stdbool.h>
#include <stdint.h>

#define WORDLINES 2048
#define BITLINES 512

typedef struct Memcell8 Memcell8;
typedef struct RamTile RamTile;
typedef struct RamBank RamBank;
typedef struct RamChip RamChip;
typedef struct DIMM DIMM;

struct Memcell8
{
    uint8_t value;
};

struct RamBank 
{
    Memcell8 cellblock[WORDLINES][BITLINES/8];
    uint8_t bitlineBits8[BITLINES/8];
};

struct RamChip 
{
    RamBank bank[32];
};

struct DIMM
{
    RamChip chip[8];
};

void ram_access(DIMM *dimm, uint32_t adress22, bool we, uint64_t *datawire);

#endif