#include "functions.h"

int main() {
    
    int qtd_simulacoes = get_int("Quantos algoritmos deseja executar?  (1-7)");
    while (qtd_simulacoes < 1 || qtd_simulacoes > 7)
    {
        printf("Por Favor, insira um numero entre (1-7) ");
        qtd_simulacoes = get_int("");
    }
    
    Simulacao* sims = malloc(qtd_simulacoes * sizeof(Simulacao));

    if (sims == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para as simulacoes.\n");
        return 1;
    }

    int tipo = menu_tipo_vetor(tipo);
    char vetor_tipo[SIZE_NAME];

    int tamanho = get_int("Informe o tamanho do vetor: ");
    int* v = NULL;

    switch (tipo) {
        case 1:
            v = vetor_aleatorio(tamanho);
            strcpy(vetor_tipo, "Aleatorio");
            break;
        case 2:
            v = vetor_crescente(tamanho);
            strcpy(vetor_tipo, "Crescente");
            break;
        case 3:
            v = vetor_decrescente(tamanho);
            strcpy(vetor_tipo, "Decrescente");
            break;
        default:
            printf("Opcao invalida.\n");
            exit(1);
    }

    if (v == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para o vetor.\n");
        exit(1);
    }

    int* backup = malloc(tamanho * sizeof(int));
    if (backup == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para o backup.\n");
        free(v);
        exit(1);
    }
    memcpy(backup, v, tamanho * sizeof(int));

    for (int i = 0; i < qtd_simulacoes; i++) {
        printf("\n----- SIMULACAO %d -----\n", i + 1);
        Simulacao sim;

        printf("\nDeseja imprimir o vetor original? (1 = Sim / 0 = Nao): ");
        int imprimir_original = get_int("");
        if (imprimir_original == 1) {
            imprimir(v, tamanho);
        }

        int opcao = menu_algoritmo();
        L comparacoes = 0, trocas = 0;
        clock_t inicio, fim;
        double tempo_ms;

        switch (opcao) {
            case 1:
                strcpy(sim.algoritmo, "Selection");
                selection_sort(v, tamanho);
                break;
            case 2:
                strcpy(sim.algoritmo, "Insertion");
                insertion_sort(v, tamanho);
                break;
            case 3:
                strcpy(sim.algoritmo, "Bubble");
                bubble_sort(v, tamanho);
                break;
            case 4:
                strcpy(sim.algoritmo, "Quick");
                quick_sort(v, 0, tamanho - 1);
                break;
            case 5:
                strcpy(sim.algoritmo, "Merge");
                merge_sort(v, 0, tamanho - 1);
                break;
            case 6:
                strcpy(sim.algoritmo, "Counting");
                counting_sort(v, tamanho, &comparacoes, &trocas);
                break;
            case 7:
                strcpy(sim.algoritmo, "Radix");
                radix_sort(v, tamanho, &comparacoes, &trocas);
                break;
            default:
                printf("Opcao invalida.\n");
                free(v);
                free(backup);
                sim.tamanho = 0;
                sims[i] = sim;
                continue;
        }

        sim.tamanho = tamanho;
        sim.tempo_ms = tempo_ms;
        sim.trocas = trocas;
        sim.comparacoes = comparacoes;

        imprimir_resultado(sim, vetor_tipo);

        printf("\nDeseja imprimir o vetor ordenado? (1 = Sim / 0 = Nao): ");
        int imprimir_final = get_int("");
        if (imprimir_final == 1) {
            imprimir(v, tamanho);
        }

        sims[i] = sim;
        free(v);
        free(backup);
    }

    imprimir_resumo(sims, qtd_simulacoes, vetor_tipo);
    free(sims);
    return 0;
}