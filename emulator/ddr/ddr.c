#include <stdbool.h>

typedef struct Transistor Transistor;
typedef struct Memcell Memcell;

struct Transistor {
    bool source;
    bool drain;
    bool gate;
};

struct Memcell
{
    Transistor transistor;
    bool capacitor;
};

void toggleGateT(Transistor *t) {
    t->gate = !(t->gate);
    if (t->gate) {
        t->drain = t->source;
    }
}

void toggleGateC(Memcell *cell) {
    toggleGateT(&cell->transistor);
    if(cell->transistor.gate && !cell->transistor.source) {
        cell->transistor.source = cell->capacitor;
    }
    if(!cell->transistor.gate) {
        cell->capacitor = cell->transistor.drain;
        cell->transistor.drain = 0;
    }
}

int main(int argc, char const *argv[])
{
    Memcell cell = {0};


    return 0;
}
