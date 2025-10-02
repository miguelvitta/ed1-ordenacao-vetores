#include "functions.h"
// Não inclua outras bibliotecas, inclua em functions.h

int main() {
    int* v = Aleatorio(10);
    CountingSort(v,10);
    Imprimir(v,10);

    return 0;
}