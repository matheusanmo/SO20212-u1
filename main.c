#include "matrix.h"
#include <stdio.h> // printf
#include <string.h>   // strcmp

/**
 * Imprime texto de ajuda da invocacao para gerar matrizes.
 */
void print_help_auxiliar() {
    printf("  `matrix aux linhas colunas filename`:\n");
    printf("    gera matrix de inteiros de tamanho linhas x colunas e salva em filename (sera truncado)\n");
    return;
}

/**
 * Imprime texto de ajuda da invocacao no stdout.
 */
void print_help() {
    printf("usage: `matrix {help, aux, seq, thr, frk, test} [args]`\n");
    print_help_auxiliar();
    return;
}

int main(int argc, char* argv[]) {
    if (argc < 2 || !strcmp(argv[1], "help")) {
        print_help();
        return 0;
    }

    if (!strcmp(argv[1], "test")) {
        matrix_test_routine();
        return 0;
    }

    if (!strcmp(argv[1], "aux")) {
        if (argc < 5) {
            print_help_auxiliar();
            return 0;
        }
        //auxiliar(strtol(argv[2], NULL, 10), strtol(argv[3], NULL, 10), argv[4]);
        return 0;
    }

    printf("Maus argumentos.\n");
    print_help();
    return 1;
}


