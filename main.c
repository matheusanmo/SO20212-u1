/**
 * Ponto de entrada do programa e funcoes relacionadas a operacao via CLI
 */
#include "matrix.h"
#include "auxiliar.h"
#include "sequential.h"
#include "timetools.h"
#include <stdlib.h> // strtol
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
 * Imprime texto de ajuda da invocacao para multiplicacao serial.
 */
void print_help_sequential() {
    printf("  `matrix seq m1 m2 mout`:\n");
    printf("    m1   caminho para matriz A\n");
    printf("    m2   caminho para matriz B\n");
    printf("    mout caminho para gravar matriz AB\n");
    return;
}

/**
 * Imprime texto de ajuda da invocacao no stdout.
 */
void print_help() {
    printf("usage: `matrix {help, aux, seq, thr, frk, test} [args]`\n");
    print_help_auxiliar();
    print_help_sequential();
    return;
}

int main(int argc, char* argv[]) {
    if (argc < 2 || !strcmp(argv[1], "help")) {
        print_help();
        return 0;
    }

    if (!strcmp(argv[1], "test")) {
        matrix_test_routine();
        timetools_test_routine();
        return 0;
    }

    if (!strcmp(argv[1], "aux")) {
        if (argc < 5) {
            print_help_auxiliar();
            return 0;
        }
        int lines      = strtol(argv[2], NULL, 10);
        int cols       = strtol(argv[3], NULL, 10);
        char* filepath = argv[4];
        auxiliar(filepath, lines, cols);
        return 0;
    }

    if (!strcmp(argv[1], "seq")) {
        if (argc < 5) {
            print_help_sequential();
            return 0;
        }
        char* m1   = argv[2];
        char* m2   = argv[3];
        char* mout = argv[4];
        sequential(m1, m2, mout);

        return 0;
    }

    printf("Maus argumentos.\n");
    print_help();
    return 1;
}


