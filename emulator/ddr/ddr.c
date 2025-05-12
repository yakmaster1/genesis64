#include "ddr.h"

// [ 16 RAS = [5 BANK SEL] [11 WL SEL] ][ 6 CAS ]
// 22 Bit adress
#define BL_MASK 0b111111111
#define WL_MASK 0b11111111111

#define ADR_MASK 0b1111111111111111111111
#define CAS_MASK 0b111111

void prechargeBitlines(RamBank *bank) {
    for (int i = 0; i < BITLINES/8; i++)
    {
        bank->bitlineBits8[i] = 0;
    }
}

void setWordlineImpulse(RamBank *bank, uint16_t row) {
    uint16_t rowMasked = row & WL_MASK;
    for (int i = 0; i < BITLINES/8; i++)
    {
        bank->cellblock[rowMasked][i].value |= bank->bitlineBits8[i];
        bank->bitlineBits8[i] |= bank->cellblock[rowMasked][i].value;
    }
}

uint8_t colmuxram_readBL(RamBank *bank, uint8_t cas) {
    uint8_t casMasked = cas & 0b111111;
    return bank->bitlineBits8[casMasked];
}

void colmuxram_writeBL(RamBank *bank, uint8_t cas, uint8_t value) {
    uint8_t casMasked = cas & 0b111111;
    bank->bitlineBits8[casMasked] = value;
}

void ram_access(DIMM *dimm, uint32_t adress22, bool we, uint64_t *datawire) {
    uint32_t adrMasked = adress22 & ADR_MASK;
    uint16_t ras = adress22 >> 6;
    uint8_t cas = adress22 & CAS_MASK;

    uint8_t bankSel = ras >> 11;
    uint16_t wlSel = ras & WL_MASK;
    
    for (int i = 0; i < 8; i++)
    {
        RamBank *bank = &dimm->chip[7 - i].bank[bankSel];
        
        prechargeBitlines(bank);
        if (we) {
            uint8_t value = (*datawire >> (i*8));
            colmuxram_writeBL(bank, cas, value);
            setWordlineImpulse(bank, wlSel);
        } else {
            setWordlineImpulse(bank, wlSel);
            uint8_t value = colmuxram_readBL(bank, cas);
            *datawire |= ((uint64_t)value << (i*8));
        }
    }
}
