#include "functions.h"
// Não inclua outras bibliotecas, inclua em functions.h

int main() {
    int n = 10000;
    long long int comparacoes,trocas;
    int* v = Aleatorio(n);
    tempoMS(RadixSort,v,n,&comparacoes,&trocas);
    free(v);
    return 0;
}