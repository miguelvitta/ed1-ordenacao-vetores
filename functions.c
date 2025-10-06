#include "functions.h"

// ---- Menus ----
void menu_tipo_vetor() {
    printf("\nSelecione o tipo de vetor:\n");
    printf("1. Aleatorio\n");
    printf("2. Crescente\n");
    printf("3. Decrescente\n");
}

void menu_algoritmo() {
    printf("\nEscolha o algoritmo de ordenacao:\n");
    printf("1. Selection Sort\n");
    printf("2. Insertion Sort\n");
    printf("3. Bubble Sort\n");
    printf("4. Quick Sort\n");
    printf("5. Merge Sort\n");
    printf("6. Counting Sort\n");
    printf("7. Radix Sort\n");
}

// ---- Saída ----
void imprimir_resultado(Simulacao sim, char* vetor_tipo) {
    printf("\n----- RESULTADO -----\n");
    printf("Algoritmo: %s\n", sim.algoritmo);
    printf("Tipo de vetor: %s\n", vetor_tipo);
    printf("Tamanho: %d\n", sim.tamanho);
    printf("Tempo de Execucao: %.3lf ms\n", sim.tempo_ms);
    printf("Comparacoes: %llu\n", sim.comparacoes);
    printf("Trocas: %llu\n", sim.trocas);
}

void imprimir_resumo(Simulacao* sims, int qtd, char* vetor_tipo) {
    printf("\n----- RESUMO DAS SIMULACOES -----\n");
    for (int i = 0; i < qtd; i++) {
        printf(
            "%d) Algoritmo: %s | Tipo: %s | Tamanho: %d | Tempo: %.3lf ms | "
            "Comp: %lu | Trocas: %lu\n",
            i + 1, sims[i].algoritmo, vetor_tipo, sims[i].tamanho,
            sims[i].tempo_ms, sims[i].comparacoes, sims[i].trocas);
    }
}

// ---- Utilitários ----
int get_int(const char* prompt) {
    int valor = 0;
    char buffer[SIZE_BUFFER];
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            char* endptr = NULL;
            valor = strtol(buffer, &endptr, 10);
            while (*endptr == ' ' || *endptr == '\t') {
                endptr++;
            }
            if (*endptr == '\0' || *endptr == '\n') {
                return valor;
            }
            printf("Input inválido. Favor entrar um número inteiro.\n");
        } else {
            printf("Erro ao ler o input.\n");
            exit(1);
        }
    }
}

void imprimir(int* v, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

// ---- Geração de vetores ----
int* vetor_crescente(int tamanho) {
    int* v = malloc(tamanho * sizeof(int));
    if (v == NULL) {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }
    for (int i = 0; i < tamanho; i++) {
        v[i] = i + 1;
    }
    return v;
}

int* vetor_decrescente(int tamanho) {
    int* v = malloc(tamanho * sizeof(int));
    if (v == NULL) {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }
    for (int i = 0; i < tamanho; i++) {
        v[i] = tamanho - i;
    }
    return v;
}

int* vetor_aleatorio(int tamanho) {
    int* v = malloc(tamanho * sizeof(int));
    if (v == NULL) {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }
    srand(time(NULL));
    for (int i = 0; i < tamanho; i++) {
        v[i] = rand() % SIZE_NUMBER;
    }
    return v;
}

// ---- Algoritmos de ordenação ----
void selection_sort(int* v, int tamanho, L* comparacoes, L* trocas) {
    *trocas = 0;
    *comparacoes = 0;

    for (int i = 0; i < tamanho - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < tamanho; j++) {
            (*comparacoes)++;
            if (v[j] < v[menor]) {
                menor = j;
            }
        }
        if (menor != i) {
            int aux = v[i];
            v[i] = v[menor];
            v[menor] = aux;
            (*trocas)++;
        }
    }
}

void insertion_sort(int* v, int tamanho, L* comparacoes, L* trocas) {
    *trocas = 0;
    *comparacoes = 0;
    for (int i = 1; i < tamanho; i++) {
        int chave = v[i];
        int j = i - 1;
        (*comparacoes)++;
        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            (*trocas)++;
            j--;
            if (j >= 0) {
                (*comparacoes)++;
            }
        }
        v[j + 1] = chave;
    }
}

void bubble_sort(int* v, int tamanho, L* comparacoes, L* trocas) {
    *trocas = 0;
    *comparacoes = 0;

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            (*comparacoes)++;
            if (v[j] > v[j + 1]) {
                int aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
                (*trocas)++;
            }
        }
    }
}

static int pivo(int* v, int esquerda, int direita, L* comp, L* trocas) {
    int pivot = v[esquerda];
    int i = esquerda + 1;
    int pos_final = esquerda;

    for (int j = esquerda + 1; j <= direita; j++) {
        (*comp)++;
        if (v[j] < pivot) {
            pos_final++;
            int temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            i++;
            (*trocas)++;
        }
    }

    v[esquerda] = v[pos_final];
    v[pos_final] = pivot;
    (*trocas)++;
    return pos_final;
}

void quick_sort(int* v, int esquerda, int direita, L* comp, L* trocas) {
    if (esquerda < direita) {
        int p = pivo(v, esquerda, direita, comp, trocas);
        quick_sort(v, esquerda, p - 1, comp, trocas);
        quick_sort(v, p + 1, direita, comp, trocas);
    }
}

static void merge(int* v, int esquerda, int meio, int direita, L* comp,
                  L* trocas) {
    int size_esquerda = meio - esquerda + 1;
    int size_direita = direita - meio;

    int* E = malloc(size_esquerda * sizeof(int));
    int* D = malloc(size_direita * sizeof(int));
    if (E == NULL || D == NULL) {
        fprintf(stderr, "Alocação de memória falhou!\n");
        exit(1);
    }

    for (int i = 0; i < size_esquerda; i++) {
        E[i] = v[esquerda + i];
        (*trocas)++;
    }
    for (int i = 0; i < size_direita; i++) {
        D[i] = v[meio + 1 + i];
        (*trocas)++;
    }

    int i = 0;
    int j = 0;
    int k = esquerda;
    while (i < size_esquerda && j < size_direita) {
        (*comp)++;
        if (E[i] <= D[j]) {
            v[k++] = E[i++];
        } else {
            v[k++] = D[j++];
        }
        (*trocas)++;
    }
    while (i < size_esquerda) {
        v[k++] = E[i++];
        (*trocas)++;
    }
    while (j < size_direita) {
        v[k++] = D[j++];
        (*trocas)++;
    }

    free(E);
    free(D);
}

void merge_sort(int* v, int esquerda, int direita, L* comp, L* trocas) {
    if (esquerda < direita) {
        int meio = (esquerda + direita) / 2;
        merge_sort(v, esquerda, meio, comp, trocas);
        merge_sort(v, meio + 1, direita, comp, trocas);
        merge(v, esquerda, meio, direita, comp, trocas);
    }
}

static int get_max(const int* v, int tamanho, L* comparacoes) {
    int maior = v[0];
    for (int i = 1; i < tamanho; i++) {
        if (v[i] > maior) {
            maior = v[i];
        }
        (*comparacoes)++;
    }
    return maior;
}

void counting_sort(int* v, int tamanho, L* comparacoes, L* trocas) {
    *comparacoes = 0;
    *trocas = 0;
    int maior = get_max(v, tamanho, comparacoes);

    int* contador = calloc(maior + 1, sizeof(int));

    for (int i = 0; i < tamanho; i++) {
        contador[v[i]]++;
    }

    for (int i = 1; i <= maior; i++) {
        contador[i] = contador[i - 1] + contador[i];
    }
    int* saida = malloc(tamanho * sizeof(int));
    for (int i = tamanho - 1; i >= 0; i--) {
        saida[--contador[v[i]]] = v[i];
        (*trocas)++;
    }
    for (int i = 0; i < tamanho; i++) {
        v[i] = saida[i];
        (*trocas)++;
    }
    free(contador);
    free(saida);
}

static void counting_sort_radix(int* v, int tamanho, int exp, L* trocas) {
    int* saida = malloc(tamanho * sizeof(int));
    int i = 0;
    int contador[10] = {0};
    for (i = 0; i < tamanho; i++) {
        contador[(v[i] / exp) % 10]++;
    }
    for (i = 1; i < 10; i++) {
        contador[i] += contador[i - 1];
    }
    for (i = tamanho - 1; i >= 0; i--) {
        saida[contador[(v[i] / exp) % 10] - 1] = v[i];
        (*trocas)++;
        contador[(v[i] / exp) % 10]--;
    }
    for (i = 0; i < tamanho; i++) {
        v[i] = saida[i];
        (*trocas)++;
    }
    free(saida);
}

void radix_sort(int* v, int tamanho, L* comparacoes, L* trocas) {
    *comparacoes = 0;
    *trocas = 0;
    int m = get_max(v, tamanho, comparacoes);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        counting_sort_radix(v, tamanho, exp, trocas);
    }
}

// ---- Função auxiliar de medição de tempo ----
double tempo_ms(void (*sort)(int*, int, L*, L*), int* v, int tamanho, L* comp,
                L* trocas) {
    clock_t inicio, fim;
    inicio = clock();
    sort(v, tamanho, comp, trocas);
    fim = clock();
    return ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
}

// Benchmark para QuickSort
double tempo_quick(int* v, int tamanho, L* comp, L* trocas) {
    clock_t inicio, fim;
    inicio = clock();
    quick_sort(v, 0, tamanho - 1, comp, trocas);
    fim = clock();
    return ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
}

// Benchmark para MergeSort
double tempo_merge(int* v, int tamanho, L* comp, L* trocas) {
    clock_t inicio, fim;
    inicio = clock();
    merge_sort(v, 0, tamanho - 1, comp, trocas);
    fim = clock();
    return ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
}