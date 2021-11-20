#ifndef THREADED_H_
#define THREADED_H_

#include "matrix.h"
#include <sys/time.h> // timeval
#include <stdio.h>    // FILE

struct ThreadArg {
    Matrix m1, m2;
    int first_index, last_index; /// [first, last) half open, i.e. calcula elementos de indice i tq first_index <= i < last_index
    struct timeval t0;
};

/**
 * Ponto de entrada da rotina de calculo de multiplicacao matricial usando threads.
 * @param m1_path   matriz esquerda da multiplicacao
 * @param m2_path   matriz direita da multiplicacao
 * @param times_out arquivo onde serao salvos tempo de execucao de cada thread em milisegundos
 * @param p         quantidade de elementos que cada thread deve calcular
 */
void threaded(char* m1_path, char* m2_path, char* times_out, int p);
 
/**
 * Ponto de entrada para threads que vao calcular elementos da matriz produto. O arquivo de retorno 
 * e temporario e deve ser fechado com `fclose()`. O arquivo de texto contem o tempo em milisegundos 
 * que esta thread levou para calcular os elementos pedidos.
 */
FILE* thread_start(struct ThreadArg* ta);

/**
 * Wrapper `thread_start()` para uma funcao de `void*` para `void*`.
 *
 * @see thread_start()
 */
void* thread_start_void(void* ta);


#endif

