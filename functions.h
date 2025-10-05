#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// as bibliotecas vão aqui em ordem alfabética
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int64_t L;

typedef struct {
    int tamanho;
    char tipo[20];
    char algoritmo[20];
    double tempo_ms;
    L trocas;
    L comparacoes;
} Simulacao;

// ---- Menus ----
int menu_tipo_vetor();
int menu_algoritmo();

// ---- Saída ----
void imprimir_resultado(Simulacao sim);
void imprimir_resumo(Simulacao* sims, int qtd);

// ---- Utilitários ----
int get_int(const char* prompt);
void imprimir(int* v, int n);

// ---- Geração de vetores ----
int* vetor_aleatorio(int n);
int* vetor_decrescente(int n);
int* vetor_crescente(int n);

// ---- Algoritmos de ordenação ----
void selection_sort(int* v, int n);
void insertion_sort(int* v, int n);
void bubble_sort(int* v, int n);
void quick_sort(int* v, int low, int high);
void merge_sort(int* v, int left, int right);
void counting_sort(int* v, int n, L* comparacoes, L* trocas);
void radix_sort(int* v, int n, L* comparacoes, L* trocas);

// ---- Função auxiliar de medição de tempo ----
void tempo_ms(void (*sort)(int*, int, L*, L*), int* v, int n, L* comp,
              L* trocas);

#endif