#include "matrix.h"
#include <stdlib.h> // malloc free NULL
#include <stdio.h>  // FILE fprintf fopen 
#include <unistd.h> // ftruncate

Matrix matrix_new(int lines, int columns) {
    if (lines <= 0 || columns <= 0)
        return (Matrix){ lines, columns, NULL };
    return (Matrix){ lines, columns, calloc(lines * columns, sizeof(int)) };
}

void matrix_set(Matrix m, int line, int col, int elem) {
    m.elems[matrix_coord_index(m, line, col)] = elem;
}

void matrix_destroy(Matrix* m) {
    m->lines   = -1;
    m->columns = -1;
    free(m->elems);
    m->elems   = NULL;
}

void matrix_write(FILE* out, Matrix m) {
    // truncando arquivo de saida
    ftruncate((int)out, 0);
    rewind(out);

    // escrevendo linhas e colunas na primeira linha 
    fprintf(out, "dim, %d, %d\n", m.lines, m.columns);

    // salvar matrix no arquivo de texto
    int i_elem = 0;
    for (int i = 1; i <= m.lines; i++) {
        for (int j = 1; j <= m.columns; j++) {
            fprintf(out, "elem, %d, %d, %d\n", i, j,  m.elems[i_elem]);
            i_elem++;
        }
    }
    return;
}

Matrix matrix_read(FILE* in) {
    // ler dimensoes na primeira linha
    rewind(in);
    int lines, cols;
    fscanf(in, "dim, %d, %d\n", &lines, &cols);

    Matrix ret = matrix_new(lines, cols);

    for (int line_i = 0; line_i < lines * cols; line_i++) {
        int line, col, elem;
        fscanf(in, "elem, %d, %d, %d\n", &line, &col, &elem);
        matrix_set(ret, line, col, elem);
    }
    return ret;
}

int matrix_coord_index(Matrix m, int line, int col) {
    return (line - 1) * m.columns + (col - 1);
}

void matrix_index_coord(Matrix m, int index, int linecol[2]) {
    linecol[0] = index / m.columns + 1;
    linecol[1] = index % m.columns + 1;
    return;
}

void matrix_print(Matrix m) {
    printf("Matriz %d x %d (%d elementos):\n", m.lines, m.columns, m.lines * m.columns);
    int elem_index = 0;
    for (int i = 0; i < m.lines; i++) {
        for (int j = 0; j < m.columns; j++) {
            printf("%d ", m.elems[elem_index]);
            elem_index++;
        }
        printf("\n");
    }
    printf("\n");
    return;
}

int matrix_mult_prod(Matrix m1, Matrix m2, int i, int j) {
    // cij = sigma^n_{k=1} a[i,k]*b[k,j] onde n = dimensao comum entre m1 m2
    int c_ij = 0;
    for (int k = 1; k <= m1.columns; k++) {
        int m1_i = matrix_coord_index(m1, i, k);
        int m2_i = matrix_coord_index(m2, k, j);
        c_ij     = c_ij + m1.elems[m1_i] * m2.elems[m2_i];
    }
    return c_ij;
}


void matrix_test_routine(void) {
    printf("matrix test routine.\n");

    printf("matrix_new:\n");
    Matrix m1 = matrix_new(7, 11);

    printf("matrix_print:\n");
    matrix_print(m1);

    printf("matrix_coord_index:\n");
    Matrix m2 = matrix_new(3,3);
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            m2.elems[matrix_coord_index(m2, i, j)] = i == j ? 1 : 0;
        }
    }
    matrix_print(m2);

    printf("index_coord:\n");
    int linecol[2];
    for (int i = 0; i < 77; i++) {
        matrix_index_coord(m1, i, linecol);
        printf("(%d |-> %d, %d) ", i, linecol[0], linecol[1]);
    }

    printf("\nmatrix_write:\n");
    FILE* testout = fopen("./test_matrix.txt", "w+t");
    matrix_write(testout, m2);
    printf("matrix salva em ./test_matrix.txt");

    printf("destruindo m2.\n");
    matrix_destroy(&m2);
    matrix_print(m2);

    printf("restaurando m2 do arquivo.\n");
    m2 = matrix_read(testout);
    matrix_print(m2);

    matrix_destroy(&m1);
    matrix_destroy(&m2);

    printf("matrix mult prod %d\n", matrix_mult_prod(m1, m2, 1, 1));
    int m1_elems[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    int m2_elems[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    Matrix ma = { 4, 3, m1_elems };
    Matrix mb = { 3, 4, m2_elems };
    matrix_print(ma);
    matrix_print(mb);
    int c11 = matrix_mult_prod(ma, mb, 1, 1);
    int c23 = matrix_mult_prod(ma, mb, 2, 3);
    int c44 = matrix_mult_prod(ma, mb, 4, 4);
    printf("c_1,1=%d, c_2,3=%d, c_4,4=%d\n", c11, c23, c44);

    printf("fim matrix_test_routine.\n");
    fclose(testout);
    return;
}

