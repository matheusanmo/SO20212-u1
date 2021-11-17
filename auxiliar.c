#include "auxiliar.h"
#include "timetools.h"

int auxiliar(char* filepath, int lines, int columns) {
    printf("> Gravando matriz %d, %d em %s.\n", l, c, filepath);
    Matriz m = matrix_new(lines, columns);

    // usando wall clock como seed pro rng
    srand(timeofday_usec()); 

    // gerar matrix lxc com inteiros aleatorios e escrever direto no arquivo
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            fprintf(fhandle, "%d ", rand());
        }
        fprintf(fhandle, "\n");
    }
    fclose(fhandle);
    matrix_destroy(m);
    return 0;
}

