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

void CountingSort(int* v, int n){
    int maior = v[0];

    for(int i=1;i<n;i++){
        if(v[i]>maior) maior = v[i];
    }

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
    }
    for(int i=0;i<n;i++){
        v[i]=saida[i];
    }
    free(contador);
    free(saida);

}