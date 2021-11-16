#include "matrix.h"
#include <stdlib.h> // malloc free NULL
#include <stdio.h>  // FILE fprintf fopen fclose

Matrix matrix_new(int lines, int columns) {
    if (lines <= 0 || columns <= 0)
        return (Matrix){ lines, columns, NULL };
    return (Matrix){ lines, columns, malloc(sizeof(int) * lines * columns) };
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
    linecol[1] = index % m.lines + 1;
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
    return;
}


