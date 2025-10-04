#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// as bibliotecas vão aqui em ordem alfabética
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Os protótipos das funções vão aqui

int get_int(const char *prompt);
void CountingSort(int* v, int n, long long int* comparacoes, long long int* trocas);
int getMax(int *v,int n,long long int* comparacoes);
void RadixSort(int* v, int n,long long int* comparacoes, long long int* trocas);
int* Aleatorio(int n);
int* Decrescente(int n);
int* Crescente(int n);
void Imprimir(int* v, int n);
void tempoMS(void (*sort)(int*, int, long long int*,long long int*), int *v, int n, long long int* comp, long long int* trocas);
void quicksort(int* v, int low, int high);

#endif