#include "functions.h"
// Não inclua outras bibliotecas, inclua em functions.h

int main() {
    int n = 1000000;
    int* v = Aleatorio(n);
    tempoMS(CountingSort,v,n);
    free(v);
    return 0;
}