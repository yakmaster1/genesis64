#ifndef SEQGEN_H
#define SEQGEN_H

typedef struct Seqgen Seqgen;
typedef enum Seqphase Seqphase;

enum Seqphase {
    SEQPH_IF, SEQPH_ID, SEQPH_EX, SEQPH_MEM, SEQPH_WB
};

struct Seqgen
{
    Seqphase phase;
};

Seqgen get_seqgen();
Seqphase phase_seqgen(Seqgen *seq);
void inc_seqgen(Seqgen *seq);

#endif