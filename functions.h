#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// as bibliotecas vão aqui em ordem alfabética
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE_BUFFER 101
#define SIZE_NAME 20
#define SIZE_NUMBER 1000000

typedef int64_t L;

typedef struct {
    int tamanho;
    char algoritmo[SIZE_NAME];
    double tempo_ms;
    L trocas;
    L comparacoes;
} Simulacao;

// ---- Menus ----
void menu_tipo_vetor();
void menu_algoritmo();

// ---- Saída ----
void imprimir_resultado(Simulacao sim, char* vetor_tipo);
void imprimir_resumo(Simulacao* sims, int qtd, char* vetor_tipo);

// ---- Utilitários ----
int get_int(const char* prompt);
void imprimir(int* v, int tamanho);

// ---- Geração de vetores ----
int* vetor_aleatorio(int tamanho);
int* vetor_decrescente(int tamanho);
int* vetor_crescente(int tamanho);

// ---- Algoritmos de ordenação ----
void selection_sort(int* v, int tamanho);
void insertion_sort(int* v, int tamanho);
void bubble_sort(int* v, int tamanho);
void quick_sort(int* v, int low, int high);
void merge_sort(int* v, int left, int right);
void counting_sort(int* v, int tamanho, L* comparacoes, L* trocas);
void radix_sort(int* v, int tamanho, L* comparacoes, L* trocas);

// ---- Função auxiliar de medição de tempo ----
void tempo_ms(void (*sort)(int*, int, L*, L*), int* v, int tamanho, L* comp,
              L* trocas);

#endif