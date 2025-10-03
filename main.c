#include "functions.h"
// Não inclua outras bibliotecas, inclua em functions.h

int main() {
    int n = 10000;
    int* v = Aleatorio(n);
    Imprimir(v,n);
    printf("\n\n\n");
    double tempo = tempoMS(RadixSort,v,n);
    Imprimir(v,n);
    printf("%.2f\n",tempo);
    free(v);
    return 0;
}