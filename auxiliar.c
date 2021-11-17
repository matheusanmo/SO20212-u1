#include "auxiliar.h"
#include "timetools.h"
#include "matrix.h"
#include <stdio.h> // printf
#include <stdlib.h>   // rand srand

int auxiliar(char* filepath, int lines, int columns) {
    printf("> Gravando matriz %d, %d em %s.\n", lines, columns, filepath);
    Matrix m = matrix_new(lines, columns);

    // usando wall clock como seed pro rng
    srand(timeofday_usec()); 

    for (int i = 0; i < lines * columns; i++) {
        m.elems[i] = rand();
    }
    matrix_write(filepath, m);
    matrix_destroy(&m);
    return 0;
}

