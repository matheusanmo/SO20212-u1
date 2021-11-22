#include "forked.h"

void forker(char* m1_path, char* m2_path, char* tout_path, int p) {
    // carregar m1 m2
    FILE* m1_in = fopen(m1_path, "rt");
    FILE* m2_in = fopen(m2_path, "rt");
    Matrix m1 = matrix_read(m1_in);
    Matrix m2 = matrix_read(m2_in);
    fclose(m1_in);
    fclose(m2_in);

    // Checando se matrizes tem dimensoes compativeis com a multiplicacao
    if (m1.columns != m2.lines) {
        printf("!!! ERRO: forked: recebeu matrizes de tamanhos incompativeis\n");
        printf("%d\n", __LINE__);
        return;
    }

    // definir qtd de elementos na matriz produto e qtd de processos
    int elem_count   = m1.lines * m2.columns;
    int process_count = ceil((double)elem_count / (double)p);
    printf("forked com m1='%s', m2='%s', csv_out='%s', p=%d, elem_count=%d, process_count=%d\n",
            m1_path, m2_path, tout_path, p, elem_count, process_count);

    // preparar array de pipes que serao usados para sincronizar com filhos e receber arquivo de saida
    X pipes = XX;
    // marcar tempo inicial
    struct timeval t0 = timeval_now();
    for (int i = 0; i < process_count; i++) {
        // forkar 
        // separar casos filho/pai/erro
    }
    // filho:
    // fechar ends dos pipes (todos que nao vai usar + seu read)
    // definir quais elementos calcular
    // calcular elems
    // salvar tempo em tmpfile
    // retornar tmpfile pelo pipe
    // fechar pipe
    // morrer

    // pai:
    int process_mean_time = 0;
    // preparar arquivo de saida
    FILE* tout = fopen(tout_path, "wt");
    fprintf(tout, "dim, %d, %d\n", m1.lines, m2.columns);
    // fechar todos ends write dos pipes
    // blocar para receber em ordem os tmpfile
    // receber tmpfile
    // salvar elementos no csv out
            fprintf(tout, "elem, %d, %d, %d\n", line, col, elem);
    // recalcular tempo medio
        int elapsed;
        fscanf((FILE*)retval, "time, %d", &elapsed);
        process_time_sum += elapsed;
    // fechar pipe que recebeu agr
    // fechar tmpfile
    // waitar
    // loop
    // salvar tempo medio

    // free, fclose, matrix_destroy etc
    matrix_destroy(&m1);
    matrix_destroy(&m2);
    fclose(tout);
    free(pipas);
    return;
}
