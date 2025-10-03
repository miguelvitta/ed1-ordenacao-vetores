#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// as bibliotecas vão aqui em ordem alfabética
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Os protótipos das funções vão aqui

int get_int(const char *prompt);
void CountingSort(int* v, int n);
int getMax(int *v,int n);
void RadixSort(int* v, int n);
int* Aleatorio(int n);
int* Decrescente(int n);
int* Crescente(int n);
void Imprimir(int* v, int n);
double tempoMS(void (*sort)(int*, int), int *v, int n);

#endif