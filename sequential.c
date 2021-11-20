#include "sequential.h"
#include "timetools.h"
#include "matrix.h"
#include <stdio.h> // printf fopen FILE fprintf fclose

void sequential(char* m1_path, char* m2_path, char* mout_path) {
    // TODO salvar apenas tempo em ms de execucacao
    // TODO redocumentar doxygen e ajudas do programa pra refletir mudanca
    // TODO printar no stdout tempo
    // TODO mudar formato de saida para concordar com threaded
    printf("sequential com m1='%s', m2='%s', m3='%s'\n", m1_path, m2_path, mout_path);
    Matrix m1   = matrix_read(m1_path);
    Matrix m2   = matrix_read(m2_path);

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
            // cij = sigma^n_{k=1} a[i,k]*b[k,j] onde n = dimensao comum entre m1 m2
            int cij = 0; 
            for (int k = 1; k <= m1.columns; k++) { 
                int aik = m1.elems[matrix_coord_index(m1, i, k)];
                int bkj = m2.elems[matrix_coord_index(m2, k, j)];
                cij += aik * bkj;
            }
            mout.elems[matrix_coord_index(mout, i,j)] = cij;
        }
    }
    struct timeval t1 = timeval_now();

    // salvar matriz, calcular tempo de execucao e append na matriz saida
    matrix_write(mout_path, mout);
    long dt = elapsed_miliseconds(t0, t1);
    FILE* outhandle = fopen(mout_path, "at");
    fprintf(outhandle, "%ldms\n", dt);
    fclose(outhandle);

    matrix_destroy(&m1);
    matrix_destroy(&m2);
    matrix_destroy(&mout);
    return;
}

