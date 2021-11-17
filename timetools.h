#ifndef TIMETOOLS_H_
#define TIMETOOLS_H_

#include <sys/time.h> // timeval 

/**
 * Calcula quantidade de milisegundos entre dois `timeval`, i.e., `t1 - t0`.
 *
 * @param t0 momento inicial
 * @param t1 momento final
 * @return tempo em milisegundos decorrido entre os argumentos
 */
long elapsed_miliseconds(const struct timeval t0, const struct timeval t1);

/**
 * Retorna parte microsegundos do horario UNIX como `unsigned int`. Usado
 * como seed para `srand()`.
 */
unsigned timeofday_usec();

/**
 * Usa `gettimeofday()` para retorna um timeval de agora.
 */
struct timeval timeval_now();

void timetools_test_routine();

#endif

