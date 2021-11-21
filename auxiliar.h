#ifndef AUXILIAR_H_
#define AUXILIAR_H_

/**
 * Gera matrix de `int`s aleatorios e salva num arquivo de texto. Cuidado: 
 * `filepath` sera truncado. A matriz salva pode ser lida com `matrix_read()`.
 *
 * @param lines    quantidade de linhas da matrix a ser gerada.
 * @param columns  quantidade de colunas da matrix a ser gerada.
 * @param filepath arquivo de texto no qual a matriz sera gravada.
 * @see matrix_read()
 */
void auxiliar(char* filepath, int lines, int columns);

#endif

