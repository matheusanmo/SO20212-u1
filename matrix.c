#include "matrix.h"
#include <stdlib.h> // malloc free NULL
#include <stdio.h>  // FILE fprintf fopen fclose

Matrix matrix_new(int lines, int columns) {
    if (lines <= 0 || columns <= 0)
        return (Matrix){ lines, columns, NULL };
    return (Matrix){ lines, columns, calloc(lines * columns, sizeof(int)) };
}

void matrix_destroy(Matrix* m) {
    m->lines   = -1;
    m->columns = -1;
    free(m->elems);
    m->elems   = NULL;
}

int matrix_write(char* filepath, Matrix m) {
    // escrevendo linhas e colunas na primeira linha 
    FILE* fhandle = fopen(filepath, "wt");
    fprintf(fhandle, "%d %d\n", m.lines, m.columns);

    // salvar matrix no arquivo de texto
    int i_elem = 0;
    for (int i = 0; i < m.lines; i++) {
        for (int j = 0; j < m.columns; j++) {
            fprintf(fhandle, "%d ", m.elems[i_elem]);
            i_elem++;
        }
        fprintf(fhandle, "\n");
    }
    fclose(fhandle);
    return 0;
}

Matrix matrix_read(char* filepath) {
    FILE* fhandle = fopen(filepath, "rt");
    
    // ler dimensoes na primeira linha
    int lines, cols;
    fscanf(fhandle, "%d %d\n", &lines, &cols);

    Matrix ret = matrix_new(lines, cols);

    for (int i = 0; i < lines * cols; i++) {
        fscanf(fhandle, "%d", &(ret.elems[i]));
    }

    fclose(fhandle);

    return ret;
}

int matrix_coord_index(Matrix m, int line, int col) {
    return (line - 1) * m.columns + (col - 1);
}

int matrix_index_coord(Matrix m, int index, int linecol[2]) {
    linecol[0] = index / m.columns + 1;
    linecol[1] = index % m.columns + 1;
    return 0;
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

void matrix_test_routine(void) {
    printf("matrix test routine.\n");
    Matrix m1 = matrix_new(7, 11);
    matrix_print(m1);
    printf("matrix identidade 3x3 com matrix_coord_index.\n");
    Matrix m2 = matrix_new(3,3);
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            m2.elems[matrix_coord_index(m2, i, j)] = i == j ? 1 : 0;
        }
    }
    matrix_print(m2);
    printf("checando se index_coord funciona na matrix 7x11.\n");
    int linecol[2];
    for (int i = 0; i < 77; i++) {
        matrix_index_coord(m1, i, linecol);
        printf("(%d |-> %d, %d) ", i, linecol[0], linecol[1]);
    }
    printf("salvando matriz id em ./test_matrix.txt.\n");
    matrix_write("./test_matrix.txt", m2);
    printf("destruindo m2.\n");
    matrix_destroy(&m2);
    matrix_print(m2);
    printf("restaurando m2.\n");
    m2 = matrix_read("./test_matrix.txt");
    matrix_print(m2);
    matrix_destroy(&m1);
    matrix_destroy(&m2);
    printf("fim matrix_test_routine.\n");
    return;
}


