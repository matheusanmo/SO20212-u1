#include "threaded.h"
#include "matrix.h"
#include "timetools.h"

#include <pthread.h> 
#include <math.h>     // ceil
#include <stdlib.h>   // NULL, malloc, free
#include <stdio.h>    // FILE printf fprintf tmpfile rewind
#include <sys/time.h> // timeval


void threaded(char* m1_path, char* m2_path, char* tout_path, int p) {
    // carregar m1 m2
    FILE* m1_in = fopen(m1_path, "rt");
    FILE* m2_in = fopen(m2_path, "rt");
    Matrix m1 = matrix_read(m1_in);
    Matrix m2 = matrix_read(m2_in);
    fclose(m1_in);
    fclose(m2_in);

    // Checando se matrizes tem dimensoes compativeis com a multiplicacao
    if (m1.columns != m2.lines) {
        printf("!!! ERRO: threaded: recebeu matrizes de tamanhos incompativeis\n");
        printf("%d\n", __LINE__);
        return;
    }

    // definir qtd de elementos na matriz produto e qtd de threads 
    int elem_count   = m1.lines * m2.columns;
    int thread_count = ceil((double)elem_count / (double)p);
    printf("threaded com m1='%s', m2='%s', csv_out='%s', p=%d, elem_count=%d, thread_count=%d\n",
            m1_path, m2_path, tout_path, p, elem_count, thread_count);

    // preparar array de threads para juntar depois
    pthread_t* threads = malloc(sizeof(pthread_t) * thread_count);
    // preparar array de threadargs
    struct ThreadArg* thread_args = malloc(sizeof(struct ThreadArg) * thread_count);
    for (int i = 0; i < thread_count; i++) {
        // preparar args para i-esima thread
        thread_args[i].m1          = m1;
        thread_args[i].m2          = m2;
        // [first_index, last_index)
        thread_args[i].first_index = i * p;
        thread_args[i].last_index  = (i+1) * p < elem_count ? (i+1) * p : elem_count;
    }

    // marcar tempo inicial e criar threads 
    struct timeval t0 = timeval_now();
    for (int i = 0; i < thread_count; i++) {
        thread_args[i].t0  = t0; // tempo inicial q a thread vai receber
        pthread_t* t_id    = &(threads[i]);
        void* t_arg        = (void*) (&(thread_args[i]));
        pthread_create(t_id, NULL, thread_start_void, t_arg);
    }

    // preparar arquivo de saida
    FILE* tout = fopen(tout_path, "wt");
    fprintf(tout, "dim, %d, %d\n", m1.lines, m2.columns);

    int thread_time_sum = 0;
    // juntar threads, escrever tempos de saida, fechar tmpfiles
    for (int i = 0; i < thread_count; i++) {
        void* retval;
        pthread_join(threads[i], &retval);
        int line, col, elem, fscanf_code;
        // ler todas linhas do arquivo retornado pela thread
        while (fscanf((FILE*) retval, "%d %d %d\n", &line, &col, &elem) == 3) {
            fprintf(tout, "elem, %d, %d, %d\n", line, col, elem);
        }
        int elapsed;
        fscanf((FILE*)retval, "time, %d", &elapsed);
        thread_time_sum += elapsed;
        fclose((FILE*)retval);
    }
    fprintf(tout, "time, %d\n", thread_time_sum / thread_count);
    printf("time, %d\n", thread_time_sum / thread_count);

    // free, fclose, matrix_destroy etc
    matrix_destroy(&m1);
    matrix_destroy(&m2);
    fclose(tout);
    free(threads);
    free(thread_args);
    return;
}

FILE* thread_start(struct ThreadArg* ta) {
    // abrir tmpfile
    FILE* retfile = tmpfile();

    // para usar matrix_index_coord
    Matrix fake = { ta->m1.lines, ta->m2.columns, NULL };

    // calcular elementos, salvar em tmpfile
    for (int i_elem = ta->first_index; i_elem < ta->last_index; i_elem++) {
        int ij[2];
        matrix_index_coord(fake, i_elem, ij);
        int c_ij = matrix_mult_prod(ta->m1, ta->m2, ij[0], ij[1]);
        fprintf(retfile, "%d %d %d\n", ij[0], ij[1], c_ij);
    }

    // T1
    // na ultima linha: tempo gasto iniciando thread e calculando elementos
    struct timeval t1 = timeval_now();
    fprintf(retfile, "time, %d\n", (int)elapsed_miliseconds(ta->t0, t1));

    // rewind e retornar file*
    rewind(retfile);
    return (void*) retfile;
}

void* thread_start_void(void* ta) {
    return (void*) thread_start((struct ThreadArg*) ta);
}

