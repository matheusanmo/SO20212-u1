#include "sequential.h"
#include "timetools.h"
#include "matrix.h"
#include <stdio.h> // printf fopen FILE fprintf fclose

void sequential(char* m1_path, char* m2_path, char* csv_out_path) {
    // TODO redocumentar doxygen e ajudas do programa pra refletir mudanca
    // TODO printar no stdout tempo
    // TODO mudar formato de saida para concordar com threaded
    printf("sequential com m1='%s', m2='%s', saida='%s'\n", m1_path, m2_path, csv_out_path);
    FILE* m1_f = fopen(m1_path, "rt");
    FILE* m2_f = fopen(m2_path, "rt");
    Matrix m1 = matrix_read(m1_f);
    Matrix m2 = matrix_read(m2_f);
    fclose(m1_f);
    fclose(m2_f);

    // Checando se matrizes tem dimensoes compativeis com a multiplicacao
    if (m1.columns != m2.lines) {
        printf("!!! ERRO: sequential: recebeu matrizes de tamanhos incompativeis\n");
        printf("%d\n", __LINE__);
        return;
    }

    Matrix mout = matrix_new(m1.lines, m2.columns);

    struct timeval t0 = timeval_now();
    for (int i = 1; i <= mout.lines; i++) {
        for (int j = 1; j <= mout.columns; j++) {
            mout.elems[matrix_coord_index(mout, i,j)] = matrix_mult_prod(m1, m2, i, j);
        }
    }
    struct timeval t1 = timeval_now();

    // salvar matriz, calcular tempo de execucao e append na matriz saida
    FILE* csv_out = fopen(csv_out_path, "wt");
    matrix_write(csv_out, mout);

    long dt = elapsed_miliseconds(t0, t1);
    fprintf(csv_out, "time, %ld\n", dt);

    matrix_destroy(&m1);
    matrix_destroy(&m2);
    matrix_destroy(&mout);
    fclose(csv_out);
    return;
}

