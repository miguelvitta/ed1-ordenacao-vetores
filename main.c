#include "functions.h"

int main() {
    int qtd_simulacoes = get_int("Quantos algoritmos deseja executar?  (1-7): ");
    while (qtd_simulacoes < 1 || qtd_simulacoes > 7) {
        printf("Por Favor, insira um numero entre (1-7) ");
        qtd_simulacoes = get_int("");
    }

    Simulacao* sims = malloc(qtd_simulacoes * sizeof(Simulacao));

    if (sims == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para as simulacoes.\n");
        exit(1);
    }

    menu_tipo_vetor();
    int tipo = get_int("");
    while (tipo < 1 || tipo > 3) {
        printf("Por Favor, insira um numero entre (1-3) ");
        menu_tipo_vetor();
        tipo = get_int("");
    }
    char vetor_tipo[SIZE_NAME];

    int tamanho = get_int("Informe o tamanho do vetor: ");
    while (tamanho < 1 || tamanho > 1000000) {
        printf("Por Favor, insira um numero entre (1-1000000) ");
        tamanho = get_int("");
    }

    int* original = NULL;

    switch (tipo) {
        case 1:
            original = vetor_aleatorio(tamanho);
            strcpy(vetor_tipo, "Aleatorio");
            break;
        case 2:
            original = vetor_crescente(tamanho);
            strcpy(vetor_tipo, "Crescente");
            break;
        case 3:
            original = vetor_decrescente(tamanho);
            strcpy(vetor_tipo, "Decrescente");
            break;
    }

    if (original == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para o vetor.\n");
        exit(1);
    }

    for (int i = 0; i < qtd_simulacoes; i++) {
        printf("\n----- SIMULACAO %d -----\n", i + 1);
        Simulacao sim;

        printf("\nDeseja imprimir o vetor original? (1 = Sim / 0 = Nao): ");
        int imprimir_original = get_int("");
        if (imprimir_original == 1) {
            imprimir(original, tamanho);
        }
        int* v = malloc(tamanho * sizeof(int));
        if (v == NULL) {
            fprintf(stderr, "Erro ao alocar memoria para o novo vetor.\n");
            free(v);
            exit(1);
        }
        memcpy(v, original, tamanho * sizeof(int));

        menu_algoritmo();
        int opcao = get_int("");
        while (opcao < 1 || opcao > 7) {
            printf("Por Favor, insira um numero entre (1-7) ");
            opcao = get_int("");
        }

        L comparacoes = 0, trocas = 0;
        double tempo = 0.0;

        switch (opcao) {
            case 1:
                strcpy(sim.algoritmo, "Selection");
                tempo =
                    tempo_ms(selection_sort, v, tamanho, &comparacoes, &trocas);
                break;
            case 2:
                strcpy(sim.algoritmo, "Insertion");
                tempo =
                    tempo_ms(insertion_sort, v, tamanho, &comparacoes, &trocas);
                break;
            case 3:
                strcpy(sim.algoritmo, "Bubble");
                tempo =
                    tempo_ms(bubble_sort, v, tamanho, &comparacoes, &trocas);
                break;
            case 4:
                strcpy(sim.algoritmo, "Quick");
                tempo = tempo_quick(v, tamanho, &comparacoes, &trocas);
                break;
            case 5:
                strcpy(sim.algoritmo, "Merge");
                tempo = tempo_merge(v, tamanho, &comparacoes, &trocas);
                break;
            case 6:
                strcpy(sim.algoritmo, "Counting");
                tempo =
                    tempo_ms(counting_sort, v, tamanho, &comparacoes, &trocas);
                break;
            case 7:
                strcpy(sim.algoritmo, "Radix");
                tempo = tempo_ms(radix_sort, v, tamanho, &comparacoes, &trocas);
                break;
        }

        sim.tamanho = tamanho;
        sim.tempo_ms = tempo;
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
    }

    imprimir_resumo(sims, qtd_simulacoes, vetor_tipo);
    free(sims);
    free(original);
    return 0;
}