#ifndef SEQGEN_H
#define SEQGEN_H

#include <stdbool.h>

typedef struct Seqgen Seqgen;
typedef enum Seqphase Seqphase;

enum Seqphase {
    SEQPH_F, SEQPH_D, SEQPH_E, SEQPH_I
};

struct Seqgen
{
    Seqphase phase;
};

Seqgen get_seqgen();
void inc_seqgen(Seqgen *seq);

#endif