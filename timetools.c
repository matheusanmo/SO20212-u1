#include "timetools.h"
#include <stdlib.h> // NULL
#include <sys/time.h> // gettimeofday timeval 

long elapsed_miliseconds(const struct timeval t0, const struct timeval t1) {
    long delta_sec  = (long) (t1.tv_sec  - t0.tv_sec ) * 1000; // tempo em milisegundos 
    long delta_usec = (long) (t1.tv_usec - t0.tv_usec) / 1000; // tempo em milisegundos
    return delta_sec + delta_usec;
}

unsigned timeofday_usec() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned) tv.tv_usec;
}

