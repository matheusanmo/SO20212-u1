#include "timetools.h"
#include <unistd.h> // getppid
#include <stdlib.h>   // NULL
#include <stdio.h>    // printf
#include <sys/time.h> // gettimeofday timeval 

long elapsed_miliseconds(const struct timeval t0, const struct timeval t1) {
    long delta_sec  = (long) (t1.tv_sec  - t0.tv_sec ) * 1000; // tempo em milisegundos 
    long delta_usec = (long) (t1.tv_usec - t0.tv_usec) / 1000; // tempo em milisegundos
    return delta_sec + delta_usec;
}

unsigned timeofday_usec() {
    struct timeval tv = timeval_now();
    return (unsigned) tv.tv_usec;
}

struct timeval timeval_now() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv;
}

void timetools_test_routine() {
    // TODO testar timeval_now
    printf("timetools_test_routine.\n");
    struct timeval t0 = timeval_now();
    for (int i = 0; i < 10000; i++) {
        getppid(); // fazendo syscall demorado para gastar tempo
        if (i % 1000 == 0) {
            struct timeval t1 = timeval_now();
            printf("timeofday_usec = %u, dt = %ld ms \n", timeofday_usec(), elapsed_miliseconds(t0, t1));
        }
    }
    return;
}



