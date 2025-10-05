#include "functions.h"

int main() {
    int qtd_simulacoes = get_int("Quantas simulacoes deseja executar? ");
    Simulacao* sims = malloc(qtd_simulacoes * sizeof(Simulacao));

    if (sims == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para as simulacoes.\n");
        return 1;
    }

    for (int i = 0; i < qtd_simulacoes; i++) {
        printf("\n----- SIMULACAO %d -----\n", i + 1);
        Simulacao sim;
        int tipo = menu_tipo_vetor();

        int tamanho = get_int("Informe o tamanho do vetor: ");
        int* v = NULL;

        switch (tipo) {
            case 1:
                v = vetor_aleatorio(tamanho);
                strcpy(sim.tipo, "Aleatorio");
                break;
            case 2:
                v = vetor_crescente(tamanho);
                strcpy(sim.tipo, "Crescente");
                break;
            case 3:
                v = vetor_decrescente(tamanho);
                strcpy(sim.tipo, "Decrescente");
                break;
            default:
                printf("Opcao invalida.\n");
                sim.tamanho = 0;
                sims[i] = sim;
                continue;
        }

        if (v == NULL) {
            fprintf(stderr, "Erro ao alocar memoria para o vetor.\n");
            sim.tamanho = 0;
            sims[i] = sim;
            continue;
        }

        printf("\nDeseja imprimir o vetor original? (1 = Sim / 0 = Nao): ");
        int imprimir_original = get_int("");
        if (imprimir_original == 1) {
            imprimir(v, tamanho);
        }

        int opcao = menu_algoritmo();
        L comparacoes = 0, trocas = 0;
        clock_t inicio, fim;
        double tempo_ms;

        int* backup = malloc(tamanho * sizeof(int));
        if (backup == NULL) {
            fprintf(stderr, "Erro ao alocar memoria para o backup.\n");
            free(v);
            sim.tamanho = 0;
            sims[i] = sim;
            continue;
        }
        memcpy(backup, v, tamanho * sizeof(int));

        inicio = clock();
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
        fim = clock();
        tempo_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;

        sim.tamanho = tamanho;
        sim.tempo_ms = tempo_ms;
        sim.trocas = trocas;
        sim.comparacoes = comparacoes;

        imprimir_resultado(sim);

        printf("\nDeseja imprimir o vetor ordenado? (1 = Sim / 0 = Nao): ");
        int imprimir_final = get_int("");
        if (imprimir_final == 1) {
            imprimir(v, tamanho);
        }

        sims[i] = sim;
        free(v);
        free(backup);
    }

    imprimir_resumo(sims, qtd_simulacoes);
    free(sims);
    return 0;
}