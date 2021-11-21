#include "auxiliar.h"
#include "timetools.h"
#include "matrix.h"
#include <stdio.h>  // printf FILE 
#include <stdlib.h> // rand srand 

void auxiliar(char* filepath, int lines, int columns) {
    printf("Gerando matriz %d, %d em %s.\n", lines, columns, filepath);
    Matrix m = matrix_new(lines, columns);

    // usando wall clock como seed pro rng
    srand(timeofday_usec()); 

    for (int i = 0; i < lines * columns; i++) {
        m.elems[i] = rand();
    }
    FILE* out = fopen(filepath, "wt");
    matrix_write(out, m);
    matrix_destroy(&m);
    fclose(out);
    return;
}

void auxiliar_test_routine() {
    // TODO

    return;
}


