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
        sims[i] = executar_simulacao();
    }

    imprimir_resumo(sims, qtd_simulacoes);
    free(sims);
    return 0;
}
