#include "seqgen.h"

#include <stdio.h>

Seqgen get_seqgen() {
    Seqgen seq = {0};
    seq.phase = SEQPH_F;
    return seq;
}

void inc_seqgen(Seqgen *seq) {
    switch (seq->phase)
    {
    case SEQPH_F:
        seq->phase = SEQPH_D;
        break;
    case SEQPH_D:
        seq->phase = SEQPH_E;
        break;
    case SEQPH_E:
        seq->phase = SEQPH_I;
        break;
    case SEQPH_I:
        seq->phase = SEQPH_F;
        break;    
    default:
        break;
    }
}