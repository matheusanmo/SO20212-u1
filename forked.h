#ifndef FORKED_H_
#define FORKED_H_

/**
 * Ponto de entrada da rotina de calculo de multiplicacao matricial usando processos.
 * @param m1_path   matriz esquerda da multiplicacao
 * @param m2_path   matriz direita da multiplicacao
 * @param csv_out   caminho do arquivo para salvar matriz resultado e tempo medio de execucao
 * @param p         quantidade de elementos que cada processo deve calcular
 */
void forked(char* m1_path, char* m2_path, char* times_out, int p);
#endif

