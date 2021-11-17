#include "sequential.h"
#include "timetools.h"
#include "matrix.h"
#include <stdio.h> // printf

void sequential(char* m1_path, char* m2_path, char* mout_path) {
    Matrix m1   = matrix_read(m1_path);
    Matrix m2   = matrix_read(m2_path);

    // Checando se matrizes tem dimensoes compativeis com a multiplicacao
    if (m1.columns != m2.lines) {
        printf("!!! ERRO: sequential: recebeu matrizes de tamanhos incompativeis\n");
        printf("%d\n", __LINE__);
        return;
    }

    int elem;
    for (int i = 0; i < m1.lines; i++) {
        for (int j = 0; j < m1.columns; j++) {
            printf("%d ", elem);
        }
        printf("\n");
    }
    return;
}

