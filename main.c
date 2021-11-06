#include <stdio.h>  // printf FILE fprintf fopen fclose
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

int main(int argc, char* argv[]) {
    FILE* file1 = fopen("m1", "wt");
    FILE* file2 = fopen("m2", "wt");
    auxiliar(3, 3, file1);
    auxiliar(3, 3, file2);
    fclose(file1);
    fclose(file2);
    return 0;
}

