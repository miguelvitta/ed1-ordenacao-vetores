# Algoritmos de ordenação em C

Este programa permite ao usuário gerar vetores de inteiros (random, ascending ou descending) de qualquer tamanho e ordená-los usando múltiplos algoritmos clássicos (Selection, Insertion, Bubble, Merge, Quick, Heap). Ele mede e mostra o tempo de execução, a quantidade de swaps e comparações para cada algoritmo, e pode exibir tanto o vetor original quanto o ordenado.

## Requisitos

- Um compilador C como `clang` ou `gcc`.
- `make` instalado (opcional, mas recomendado).

## Compilar e Executar com `make`

1. Abra um terminal nesta pasta.
2. Compile o programa:

   ```bash
   make
   ```
Isso gera um executável chamado sort_algorithms

Execute o programa:

```bash
./sort_algorithms
```

Para limpar arquivos objeto e o binário:

```bash
make clean
```

Para compilar com flags de debug (AddressSanitizer, symbols, sem otimizações):

```bash
make debug
./sort_algorithms
```

## Compilar e Executar Sem make
Se preferir não usar make, compile manualmente:

```bash
clang -Wall -Wextra -Wshadow main.c functions.c -o sort_algorithms -lm
```

Depois execute:

```bash
./sort_algorithms
```

Substitua clang por gcc se desejar.

---