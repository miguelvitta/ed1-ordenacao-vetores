#include "functions.h"

#define SIZE_BUFFER 101
#define SIZE_NUMBER 100000

// ---- Menus ----
int menu_tipo_vetor() {
    printf("\nSelecione o tipo de vetor:\n");
    printf("1. Aleatorio\n");
    printf("2. Crescente\n");
    printf("3. Decrescente\n");
    int tipo = get_int("Opcao: ");
    return tipo;
}

int menu_algoritmo() {
    printf("\nEscolha o algoritmo de ordenacao:\n");
    printf("1. Selection Sort\n");
    printf("2. Insertion Sort\n");
    printf("3. Bubble Sort\n");
    printf("4. Quick Sort\n");
    printf("5. Merge Sort\n");
    printf("6. Counting Sort\n");
    printf("7. Radix Sort\n");

    int opcao = get_int("Opcao: ");
    return opcao;
}

// ---- Saída ----
void imprimir_resultado(Simulacao sim) {
    printf("\n----- RESULTADO -----\n");
    printf("Algoritmo: %s\n", sim.algoritmo);
    printf("Tipo de vetor: %s\n", sim.tipo);
    printf("Tamanho: %d\n", sim.tamanho);
    printf("Tempo de Execucao: %.3lf ms\n", sim.tempo_ms);
    printf("Comparacoes: %lld\n", sim.comparacoes);
    printf("Trocas: %lld\n", sim.trocas);
}

void imprimir_resumo(Simulacao* sims, int qtd) {
    printf("\n----- RESUMO DAS SIMULACOES -----\n");
    for (int i = 0; i < qtd; i++) {
        printf(
            "%d) Algoritmo: %s | Tipo: %s | Tamanho: %d | Tempo: %.3lf ms | "
            "Comp: %lld | Trocas: %lld\n",
            i + 1, sims[i].algoritmo, sims[i].tipo, sims[i].tamanho,
            sims[i].tempo_ms, sims[i].comparacoes, sims[i].trocas);
    }
}

// ---- Execução ----
Simulacao executar_simulacao() {
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
            return sim;
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
            return sim;
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

    free(v);
    free(backup);
    return sim;
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
            printf("Invalid input. Please enter an integer.\n");
        } else {
            printf("Error reading input.\n");
            exit(1);
        }
    }
}

void imprimir(int* v, int n) {
    for (int i = 0; i < n; i++) {
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
void selection_sort(int* v, int n) {
    L trocas = 0;
    L comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j] < v[menor]) {
                menor = j;
            }
        }
        if (menor != i) {
            int aux = v[i];
            v[i] = v[menor];
            v[menor] = aux;
            trocas++;
        }
    }

    // printf("SelectionSort -> Trocas: %lld | Comparacoes: %lld\n", trocas,
    // comparacoes);
}

void insertion_sort(int* v, int n) {
    L trocas = 0;
    L comparacoes = 0;

    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;
            if (v[j] > chave) {
                v[j + 1] = v[j];
                trocas++;
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
        trocas++;
    }

    // printf("InsertionSort -> Trocas: %lld | Comparacoes: %lld\n", trocas,
    // comparacoes);
}

void bubble_sort(int* v, int n) {
    L trocas = 0;
    L comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (v[j] > v[j + 1]) {
                int aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
                trocas++;
            }
        }
    }

    // printf("BubbleSort -> Trocas: %lld | Comparacoes: %lld\n", trocas,
    // comparacoes);
}

static int pivo(int* v, int esquerda, int direita) {
    int pivot = v[esquerda];
    int i = esquerda + 1;
    int pos_final = esquerda;

    for (int j = esquerda + 1; j <= direita; j++) {
        if (v[j] < pivot) {
            pos_final++;
            // talvez colocar em função de troca separada na fase de acabamento
            // do projeto
            int temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            i++;
        }
    }

    v[esquerda] = v[pos_final];
    v[pos_final] = pivot;
    return pos_final;
}

void quick_sort(int* v, int esquerda, int direita) {
    if (esquerda < direita) {
        int p = pivo(v, esquerda, direita);
        quick_sort(v, esquerda, p - 1);
        quick_sort(v, p + 1, direita);
    }
}

static void merge(int* v, int esquerda, int meio, int direita) {
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
    }
    for (int i = 0; i < size_direita; i++) {
        D[i] = v[meio + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = esquerda;
    while (i < size_esquerda && j < size_direita) {
        if (E[i] <= D[j]) {
            v[k++] = E[i++];
        } else {
            v[k++] = D[j++];
        }
    }
    while (i < size_esquerda) {
        v[k++] = E[i++];
    }
    while (j < size_direita) {
        v[k++] = D[j++];
    }

    free(E);
    free(D);
}

void merge_sort(int* v, int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = (esquerda + direita) / 2;
        merge_sort(v, esquerda, meio);
        merge_sort(v, meio + 1, direita);
        merge(v, esquerda, meio, direita);
    }
}

static int get_max(int* v, int n, L* comparacoes) {
    int maior = v[0];
    for (int i = 1; i < n; i++) {
        if (v[i] > maior) {
            maior = v[i];
        }
        (*comparacoes)++;
    }
    return maior;
}

void counting_sort(int* v, int n, L* comparacoes, L* trocas) {
    *comparacoes = 0;
    *trocas = 0;
    int maior = get_max(v, n, comparacoes);

    int* contador = calloc(maior + 1, sizeof(int));

    for (int i = 0; i < n; i++) {
        contador[v[i]]++;
    }

    for (int i = 1; i <= maior; i++) {
        contador[i] = contador[i - 1] + contador[i];
    }
    int* saida = malloc(n * (sizeof(int)));
    for (int i = n - 1; i >= 0; i--) {
        saida[--contador[v[i]]] = v[i];
        (*trocas)++;
    }
    for (int i = 0; i < n; i++) {
        v[i] = saida[i];
        (*trocas)++;
    }
    free(contador);
    free(saida);
}

static void counting_sort_radix(int* v, int n, int exp, L* trocas) {
    int* saida = malloc(n * sizeof(int));
    int i;
    int contador[10] = {0};
    for (i = 0; i < n; i++) {
        contador[(v[i] / exp) % 10]++;
    }
    for (i = 1; i < 10; i++) {
        contador[i] += contador[i - 1];
    }
    for (i = n - 1; i >= 0; i--) {
        saida[contador[(v[i] / exp) % 10] - 1] = v[i];
        (*trocas)++;
        contador[(v[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++) {
        v[i] = saida[i];
        (*trocas)++;
    }
    free(saida);
}

void radix_sort(int* v, int n, L* comparacoes, L* trocas) {
    *comparacoes = 0;
    *trocas = 0;
    int m = get_max(v, n, comparacoes);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        counting_sort_radix(v, n, exp, trocas);
    }
}

// ---- Função auxiliar de medição de tempo ----
void tempo_ms(void (*sort)(int*, int, L*, L*), int* v, int n, L* comp,
              L* trocas) {
    clock_t inicio, fim;
    double tempo_ms;
    inicio = clock();
    sort(v, n, comp, trocas);
    fim = clock();
    tempo_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
    printf("Tempo de Execucao: %.3lf ms(milissegundo)\n", tempo_ms);
    printf("Comparacoes: %ld \n", (long)*comp);
    printf("Trocas: %ld \n", (long)*trocas);
}