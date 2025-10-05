#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// as bibliotecas vão aqui em ordem alfabética
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int tamanho;
    char tipo[20];
    char algoritmo[20];
    double tempo_ms;
    long long int trocas;
    long long int comparacoes;
} Simulacao;

// main
int menu_tipo_vetor();
int menu_algoritmo();
void imprimir_resultado(Simulacao sim);
void imprimir_resumo(Simulacao* sims, int qtd);
Simulacao executar_simulacao();

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
void merge_sort(int* v, int left, int right);

#endif