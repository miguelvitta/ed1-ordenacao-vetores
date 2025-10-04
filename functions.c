#include "functions.h"

#define SIZE_BUFFER 101

// As funções vão aqui

int get_int(const char *prompt) {
    int value = 0;
    char buffer[SIZE_BUFFER];
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            char *endptr = NULL;
            value = strtol(buffer, &endptr, 10);
            while (*endptr == ' ' || *endptr == '\t') {
                endptr++;
            }
            if (*endptr == '\0' || *endptr == '\n') {
                return value;
            }
            printf("Invalid input. Please enter an integer.\n");
        } else {
            printf("Error reading input.\n");
            exit(1);
        }
    }
}

int getMax(int *v,int n,long long int* comparacoes){
    int maior = v[0];
    for(int i=1;i<n;i++){
        if(v[i]>maior){
            maior = v[i];
        }
        (*comparacoes)++;
    }
    return maior;
}

void CountingSort(int* v, int n, long long int* comparacoes, long long int* trocas){
    *comparacoes = 0;
    *trocas = 0;
    int maior = getMax(v,n,comparacoes);

    int* contador = calloc(maior+1,sizeof(int));

    for(int i=0;i<n;i++){
        contador[v[i]]++;
    }

    for(int i=1; i<= maior; i++){
        contador[i] = contador[i-1] + contador[i];
    }
    int* saida = malloc(n * (sizeof(int)));
    for(int i = n-1;i>=0;i--){
        saida[--contador[v[i]]] = v[i];
        (*trocas)++;
    }
    for(int i=0;i<n;i++){
        v[i]=saida[i];
        (*trocas)++;
    }
    free(contador);
    free(saida);

}

void CountigSortRadix(int *v,int n, int exp, long long int* trocas){
    int* saida = malloc(n*sizeof(int));
    int i;
    int contador[10] = {0};
    for(i=0;i<n;i++){
        contador[(v[i]/exp)%10]++;
    }
    for(i=1;i<10;i++){
        contador[i]+=contador[i-1];
    }
    for(i=n-1;i>=0;i--){
        saida[contador[(v[i]/exp) % 10] - 1]=v[i];
        (*trocas)++;
        contador[(v[i] / exp) % 10]--;
    }
    for(i=0;i<n;i++){
        v[i]=saida[i];
        (*trocas)++;
    }
    free(saida);
}

void RadixSort(int* v, int n,long long int* comparacoes, long long int* trocas){
    *comparacoes = 0;
    *trocas = 0;
    int m = getMax(v, n,comparacoes);
    for(int exp = 1; m/exp > 0; exp *= 10){
        CountigSortRadix(v, n, exp, trocas); 
    }
}

// Selecion, Inserction e Bubble

void SelectionSort(int* v, int n){
    long long int trocas = 0;
    long long int comparacoes = 0;

    for(int i=0;i<n-1;i++){
        int menor = i;
        for(int j=i+1;j<n;j++){
            comparacoes++;
            if(v[j] < v[menor]){
                menor = j;
            }
        }
        if(menor != i){
            int aux = v[i];
            v[i] = v[menor];
            v[menor] = aux;
            trocas++;
        }
    }

    //printf("SelectionSort -> Trocas: %lld | Comparacoes: %lld\n", trocas, comparacoes);
}

void InsertionSort(int* v, int n){
    long long int trocas = 0;
    long long int comparacoes = 0;

    for(int i=1;i<n;i++){
        int chave = v[i];
        int j = i-1;

        while(j >= 0){
            comparacoes++;
            if(v[j] > chave){
                v[j+1] = v[j];
                trocas++;
                j--;
            } else {
                break;
            }
        }
        v[j+1] = chave;
        trocas++;
    }

    //printf("InsertionSort -> Trocas: %lld | Comparacoes: %lld\n", trocas, comparacoes);
}

void BubbleSort(int* v, int n){
    long long int trocas = 0;
    long long int comparacoes = 0;

    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            comparacoes++;
            if(v[j] > v[j+1]){
                int aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
                trocas++;
            }
        }
    }

    //printf("BubbleSort -> Trocas: %lld | Comparacoes: %lld\n", trocas, comparacoes);
}

int* Crescente(int n){
    int* v = malloc(n * sizeof(int));
    if(v == NULL){
        printf("Erro ao alocar memória.\n");
        return NULL;
    }
    for(int i=0;i<n;i++){
        v[i] = i+1;
    }
    return v;
}

int* Decrescente(int n){
    int* v = malloc(n * sizeof(int));
    if(v == NULL){
        printf("Erro ao alocar memória.\n");
        return NULL;
    }
    for(int i=0;i<n;i++){
        v[i] = n - i;
    }
    return v;
}

int* Aleatorio(int n){
    int* v = malloc(n * sizeof(int));
    if(v == NULL){
        printf("Erro ao alocar memória.\n");
        return NULL;
    }
    int limite = 1000;
    srand(time(NULL));
    for(int i=0;i<n;i++){
        v[i]= rand() % limite;
    }
    return v;
}

void Imprimir(int* v, int n){
    for(int i=0;i<n;i++){
        printf("%d ",v[i]);
    }
    printf("\n");
}

void tempoMS(void (*sort)(int*, int, long long int*,long long int*), int *v, int n, long long int* comp, long long int* trocas) {
    clock_t inicio, fim;
    double tempo_ms;
    inicio = clock();
    sort(v, n, comp,trocas);  
    fim = clock();
    tempo_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC)*1000.0;
    printf("Tempo de Execucao: %.3lf ms(milissegundo)\n",tempo_ms);
    printf("Comparacoes: %ld \n",(long)*comp);
    printf("Trocas: %ld \n",(long)*trocas);
}