#include <stdio.h>    // printf FILE fprintf fopen fclose rewind fscanf
#include <stdlib.h>   // malloc rand srand
#include <sys/time.h> // gettimeofday struct-timeval 

/**
 * Escreve string no stdout adornada como mensagem de teste.
 *
 * @param s string que sera imprimida como parte da mensagem de teste.
 */
void print_test(const char* s) {
    printf(">>> TESTE: %s\n", s);
    return;
}

void test_print_test() {
    print_test(__FUNCTION__);
    print_test("testando print_test");
}

/**
 * Escreve string no stdout adornada como mensagem de erro.
 *
 * @param s string que sera imprimida como parte da mensagem de erro.
 */
void print_error(const char* s) {
    printf("!!! ERRO:%s:%d:%s\n", __FILE__, __LINE__, s);
    return;
}

void test_print_error() {
    print_test(__FUNCTION__);
    print_error("test_print_error.");
}

/**
 * Retorna parte microsegundos do horario UNIX como unsigned int.
 */
unsigned timeofday_usec() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned) tv.tv_usec;
}

void test_timeofday_usec() {
    print_test(__FUNCTION__);
    printf("%u \n%u \n%u \n", timeofday_usec(), timeofday_usec(), timeofday_usec());
}

/**
 * Calcula quantidade de milisegundos entre dois `timeval`, i.e., `t1 - t0`.
 *
 * @param t0 momento inicial.
 * @param t1 momento final.
 * @return tempo em milisegundos decorrido entre t0 e t1.
 */
long elapsed_miliseconds(const struct timeval t0, const struct timeval t1) {
    long delta_sec  = (long) (t1.tv_sec  - t0.tv_sec ) * 1000; // tempo em milisegundos 
    long delta_usec = (long) (t1.tv_usec - t0.tv_usec) / 1000; // tempo em milisegundos
    return delta_sec + delta_usec;
}

void test_elapsed_miliseconds() {
    print_test(__FUNCTION__);
    struct timeval t1;
    gettimeofday(&t1, NULL);

    struct timeval t2;
    gettimeofday(&t2, NULL);
    printf("%ld\n", elapsed_miliseconds(t1, t2));

    int sink = 1;
    for (int i = 0; i < 256; i++) {
        sink += 5;
    }

    gettimeofday(&t2, NULL);
    printf("%ld\n", elapsed_miliseconds(t1, t2));
}

/**
 * Imprime texto de ajuda da invocacao para gerar matrizes.
 */
void print_help_gen() {
    printf("  `matrix gen linhas colunas filename`:\n");
    printf("    gera matrix de inteiros de tamanho linhas x colunas e salva em filename (sera truncado)\n");
    return;
}

/**
 * Imprime texto de ajuda da invocacao no stdout.
 */
void print_help() {
    printf("usage: `matrix {gen, seq, thr, proc} args`\n");
    print_help_gen();
    return;
}

/**
 * Recebe handle de um arquivo de texto contendo uma matriz gravada com
 * `auxiliar()` e retorna ponteiro para seus elementos dispostos linearmente
 * num array (alocado com `malloc`, que deve ser `free()` depois) ou NULL 
 * se a matriz tiver dimensoes indevidas.
 * 
 * @param[in,out] fhandle arquivo de texto que sera rebobinado e lido como matriz.
 * @return ponteiro para array de elementos da matriz lida ou NULL.
 * @see auxiliar()
 */
int* alloc_matrix(FILE* fhandle) {
    // rebobina arquivo e le qtd de linhas e colunas na 1a linha do texto
    rewind(fhandle);
    int lines, cols;
    fscanf(fhandle, "%d %d\n", &lines, &cols);

    // retornar NULL se a matriz tiver dimensoes indevidas
    if (lines <= 0 || cols <= 0) {
        return NULL;
    }

    // ler inteiros do arquivo recebido e guardar num array na ordem em que sao lidos
    int* matrixdata = malloc(sizeof(int) * lines * cols);
    for (int i = 1; i <= lines; i++) {
        for (int j = 1; j <= cols; j++) {
            int elemindex = (i * cols) + j - 1;
            fscanf(fhandle, "%d ", &(matrixdata[elemindex]));
            printf("elemindex %d\n", elemindex);
        }
    }
    return matrixdata;
}

void test_alloc_matrix() {
    //TODO
}

/**
 * Gera matrix de `int`s aleatorios e salva num arquivo de texto. Cuidado: 
 * `fhandle` sera truncado.
 *
 * @param      l       quantidade de linhas da matrix a ser gerada.
 * @param      c       quantidade de colunas da matrix a ser gerada.
 * @param[out] fhandle arquivo de texto no qual a matriz sera gravada.
 */
void auxiliar(int l, int c, FILE* fhandle) { 
    // escrevendo linhas e colunas na primeira linha 
    fprintf(fhandle, "%d %d\n", l, c);

    // nao fazer nada quando for pedida matrix de tamanho indefinido
    if (l <= 0 || c <= 0) { 
        return;
    }

    // usando wall clock como seed pro rng
    srand((unsigned) timeofday_usec()); 

    // gerar matrix lxc com inteiros aleatorios e escrever direto no arquivo
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            fprintf(fhandle, "%d ", rand());
        }
        fprintf(fhandle, "\n");
    }
    return;
}

void teste_auxiliar() {
    // TODO
}

void sequential(FILE* m1, FILE* m2, FILE* mout) {
    rewind(m1);
    rewind(m2);

    int lines_m1, lines_m2, cols_m1, cols_m2;
    fscanf(m1, "%d %d\n", &lines_m1, &cols_m1);
    fscanf(m2, "%d %d\n", &lines_m2, &cols_m2);
    printf("%d %d\n%d %d\n", lines_m1, cols_m1, lines_m2, cols_m2);

    if (cols_m1 != lines_m2) {
        printf("!!! ERRO: sequential: recebeu matrizes de tamanhos incompativeis\n");
        printf("%d\n", __LINE__);
        exit(-1);
    }

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
    FILE* file1   = fopen("m1", "w+t");
    FILE* file2   = fopen("m2", "w+t");
    FILE* fileseq = fopen("mseq", "w+t");
    auxiliar(3, 3, file1);
    auxiliar(3, 3, file2);
    sequential(file1, file2, fileseq);
    fclose(file1);
    fclose(file2);
    fclose(fileseq);
    return 0;
}

