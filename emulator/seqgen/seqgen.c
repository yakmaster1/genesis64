#include "seqgen.h"

Seqphase phase_seqgen(Seqgen *seq) {
    return seq->phase;
}

Seqgen get_seqgen() {
    Seqgen seq = {0};
    seq.phase = SEQPH_IF;
    return seq;
}

void inc_seqgen(Seqgen *seq) {
    switch (seq->phase)
    {
    case SEQPH_IF:
        seq->phase = SEQPH_ID;
        break;
    case SEQPH_ID:
        seq->phase = SEQPH_EX;
        break;
    case SEQPH_EX:
        seq->phase = SEQPH_MEM;
        break;
    case SEQPH_MEM:
        seq->phase = SEQPH_WB;
        break;    
    case SEQPH_WB:
        seq->phase = SEQPH_IF;
        break;  
    default:
        break;
    }
}