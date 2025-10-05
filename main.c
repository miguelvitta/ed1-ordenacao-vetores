#include "functions.h"
#include <string.h>

typedef struct{
    int tamanho;
    char tipo[20];
    char algoritmo[20];
    double tempo_ms;
    long long int trocas;
    long long int comparacoes;
} Simulacao;

int menu_tipo_vetor();
int menu_algoritmo();
void imprimir_resultado(Simulacao sim);
void imprimir_resumo(Simulacao* sims, int qtd);
Simulacao executar_simulacao();

int main(){
    int qtd_simulacoes = get_int("Quantas simulacoes deseja executar? ");
    Simulacao* sims = malloc(qtd_simulacoes * sizeof(Simulacao));

    if(sims == NULL){
        printf("Erro ao alocar memoria para as simulacoes.\n");
        return 1;
    }

    for(int i = 0; i < qtd_simulacoes; i++){
        printf("\n----- SIMULACAO %d -----\n", i+1);
        sims[i] = executar_simulacao();
    }

    imprimir_resumo(sims, qtd_simulacoes);
    free(sims);
    return 0;
}

int menu_tipo_vetor(){
    printf("\nSelecione o tipo de vetor:\n");
    printf("1. Aleatorio\n");
    printf("2. Crescente\n");
    printf("3. Decrescente\n");
    int tipo = get_int("Opcao: ");
    return tipo;
}

int menu_algoritmo(){
    printf("\nEscolha o algoritmo de ordenacao:\n");
    printf("1. Selection Sort\n");
    printf("2. Bubble Sort\n");
    printf("3. Insertion Sort\n");
    printf("4. Counting Sort\n");
    printf("5. Radix Sort\n");
    int opcao = get_int("Opcao: ");
    return opcao;
}

void imprimir_resultado(Simulacao sim){
    printf("\n----- RESULTADO -----\n");
    printf("Algoritmo: %s\n", sim.algoritmo);
    printf("Tipo de vetor: %s\n", sim.tipo);
    printf("Tamanho: %d\n", sim.tamanho);
    printf("Tempo de Execucao: %.3lf ms\n", sim.tempo_ms);
    printf("Comparacoes: %lld\n", sim.comparacoes);
    printf("Trocas: %lld\n", sim.trocas);
}

void imprimir_resumo(Simulacao* sims, int qtd){
    printf("\n----- RESUMO DAS SIMULACOES -----\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d) Algoritmo: %s | Tipo: %s | Tamanho: %d | Tempo: %.3lf ms | Comp: %lld | Trocas: %lld\n",
               i+1, sims[i].algoritmo, sims[i].tipo, sims[i].tamanho, sims[i].tempo_ms, sims[i].comparacoes, sims[i].trocas);
    }
}

Simulacao executar_simulacao(){
    Simulacao sim;
    int tipo = menu_tipo_vetor();

    int n = get_int("Informe o tamanho do vetor: ");
    int* v = NULL;

    switch (tipo) {
        case 1:
            v = Aleatorio(n);
            strcpy(sim.tipo, "Aleatorio");
            break;
        case 2:
            v = Crescente(n);
            strcpy(sim.tipo, "Crescente");
            break;
        case 3:
            v = Decrescente(n);
            strcpy(sim.tipo, "Decrescente");
            break;
        default:
            printf("Opcao invalida.\n");
            sim.tamanho = 0;
            return sim;
    }

    printf("\nDeseja imprimir o vetor original? (1 = Sim / 0 = Nao): ");
    int imprimir_original = get_int("");
    if (imprimir_original == 1){
        Imprimir(v, n);
    }

    int opcao = menu_algoritmo();
    long long int comparacoes = 0, trocas = 0;
    clock_t inicio, fim;
    double tempo_ms;

    int* backup = malloc(n * sizeof(int));
    memcpy(backup, v, n * sizeof(int));

    inicio = clock();
    switch(opcao){
        case 1:
            strcpy(sim.algoritmo, "Selection");
            SelectionSort(v, n);
            break;
        case 2:
            strcpy(sim.algoritmo, "Bubble");
            BubbleSort(v, n);
            break;
        case 3:
            strcpy(sim.algoritmo, "Insertion");
            InsertionSort(v, n);
            break;
        case 4:
            strcpy(sim.algoritmo, "Counting");
            CountingSort(v, n, &comparacoes, &trocas);
            break;
        case 5:
            strcpy(sim.algoritmo, "Radix");
            RadixSort(v, n, &comparacoes, &trocas);
            break;
        default:
            printf("Opcao invalida.\n");
            free(v);
            free(backup);
            sim.tamanho = 0;
            return sim;
    }
    fim = clock();
    tempo_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;

    sim.tamanho = n;
    sim.tempo_ms = tempo_ms;
    sim.trocas = trocas;
    sim.comparacoes = comparacoes;

    imprimir_resultado(sim);

    printf("\nDeseja imprimir o vetor ordenado? (1 = Sim / 0 = Nao): ");
    int imprimir_final = get_int("");
    if(imprimir_final == 1){
        Imprimir(v, n);
    }

    free(v);
    free(backup);
    return sim;
}