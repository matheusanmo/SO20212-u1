#include <stdio.h>  // printf FILE fprintf fopen fclose rewind fscanf
#include <stdlib.h> // malloc rand srand
#include <time.h>   // time

void auxiliar(int l, int c, FILE* fhandle) {
    fprintf(fhandle, "%d %d\n", l, c);

    // nao fazer nada quando for pedida matrix de tamanho indefinido
    if (l <= 0 || c <= 0) { 
        return;
    }

    // usando time como seed pro rng
    srand((unsigned) time(NULL)); 

    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            fprintf(fhandle, "%d ", rand());
        }
        fprintf(fhandle, "\n");
    }
    return;
}

void print_help_gen() {
    printf("  `matrix gen linhas colunas filename`:\n");
    printf("    gera matrix de inteiros de tamanho linhas x colunas e salva em filename (sera truncado)\n");
    return;
}

void print_help() {
    printf("usage: `matrix {gen, seq, thr, proc} args`\n");
    print_help_gen();
    return;
}

void sequential(FILE* m1, FILE* m2) {
    rewind(m1);
    rewind(m2);

    int lines_m1, lines_m2, cols_m1, cols_m2;
    fscanf(m1, "%d %d\n", &lines_m1, &cols_m1);
    fscanf(m2, "%d %d\n", &lines_m2, &cols_m2);
    printf("%d %d\n%d %d\n", lines_m1, cols_m1, lines_m2, cols_m2);

    int elem;
    for (int i = 0; i < lines_m1; i++) {
        for (int j = 0; j < cols_m1; j++) {
            fscanf(m1, "%d", &elem);
            printf("%d ", elem);
        }
        printf("\n");
    }

    return;
}

int main(int argc, char* argv[]) {
    FILE* file1 = fopen("m1", "w+t");
    FILE* file2 = fopen("m2", "w+t");
    auxiliar(3, 3, file1);
    auxiliar(3, 3, file2);
    sequential(file1, file2);
    fclose(file1);
    fclose(file2);
    return 0;
}

