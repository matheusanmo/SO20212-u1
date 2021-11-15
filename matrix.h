#ifndef MATRIX_H_
#define MATRIX_H_

struct Matrix {
    int  lines;   /// valores negativos indicam que essa matriz foi destruida
    int  columns; /// valores negativas indicam que essa matriz foi destruida
    int* elems;   /// `NULL` indica que essa matriz foi destruida
};

typedef struct Matrix Matrix;

/**
 * Aloca (sem inicializar) matriz do tamanho pedido. Deve ser destruida com `matrix_destroy`
 * para recuperar a memoria alocada.
 * 
 * @param lines   quantidade de linhas da matrix a ser alocada.
 * @param columns quantidade de colunas da matrix a ser alocada.
 * @return `Matrix` com tamanho pedido.
 * @see matrix_destroy()
 */
Matrix matrix_new(int lines, int columns);

/**
 * Le uma matriz gravada com `matrix_write` numa `Matrix` usando `matrix_new`. A matriz
 * retornada deve ser destruida com `matrix_destroy`.
 * 
 * @param filepath string do caminho para o arquivo de texto a ser lido.
 * @return `Matrix` lida do arquivo passado.
 * @see matrix_destroy() matrix_write()
 */
Matrix matrix_read(char* filepath);

/**
 * Grava uma `Matrix` num arquivo de texto. O arquivo a ser usado sera truncado, apagando
 * qualquer conteudo anterior. O arquivo pode ser lido com `matrix_read`.
 * 
 * @param  filepath string do caminho para o arquivo de texto a ser gravado.
 * @param  m        `Matrix` a ser gravada.
 * @return numero maiores que 0 indicam erros. 0 indica sucesso.
 * @see matrix_read()
 */
int matrix_write(char* filepath, Matrix m);

/**
 * Retorna o indice de um elemento duma matriz a partir das suas coordenadas 1-indexadas.
 * Isto e, quando `line=col=1` retorna-se o indice `0`.
 * 
 * @param line linha do elemento desejado, contando a partir de 1.
 * @param col  coluna do elemento desejado, contando a partir de 1.
 * @return indice do elemento desejado ou -1 em caso de erro.
 * @see matrix_index_coord()
 */
int matrix_coord_index(Matrix m, int line, int col);

/**
 * Calcula linha e coluna do elemento que esta no indice passado e salva 
 * a linha em `linecol[0]` e a coluna em `linecol[1]`. Ambos sao 1-indexados. 
 * Retorna numero positivo em caso de erro. 0 indica sucesso.
 * 
 * @param index indice 0-indexado da matriz e.g. `matriz.data[5]` 
 * @param[out] linecol buffer para salvar linha e coluna do elemento buscado
 * @return 0 indica sucesso, numeros positivos indicam erro
 * @see matrix_coord_index()
 */
int matrix_index_coord(Matrix m, int index, int linecol[2]);

/**
 * `free` o array subjacente a matriz passada e altera os campos desta para
 * indicar que esta matriz foi destruida.
 * 
 * @param[in,out] m `Matrix` a ser destruida
 * @see matrix_new()
 */
void matrix_destroy(Matrix* m);

#endif
