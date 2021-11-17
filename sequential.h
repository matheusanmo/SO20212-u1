#ifndef SEQUENTIAL_H_
#define SEQUENTIAL_H_

/**
 * Recebe dois arquivos de textos contendo matrizes geradas por `auxiliar()` e 
 * multiplica as duas matrizes de forma serial (sem concurrencia). Em seguida 
 * escreve em `mout` o tempo real (calculado usando `elapsed_miliseconds()`) 
 * gasto no calculo de cada elemento da matriz produto e o tempo total.
 * Cuidado: `mout` sera truncado.
 *
 * @param m1 matriz esquerda da multiplicacao
 * @param m2 matriz direita da multiplicacao
 * @param mout matriz de saida
 */
void sequential(char* m1, char* m2, char* mout);

#endif

