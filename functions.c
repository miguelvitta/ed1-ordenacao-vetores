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