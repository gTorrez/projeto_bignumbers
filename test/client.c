#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#include "bignumber.h"

int main(){
    // clock_t start, end;
    // double cpu_time_used;
    // start = clock();

    VectorInt A, B, RES;
    int operation;
    char operator;

    A = read_input();
    B = read_input();
    scanf("%c", &operator);

    operation = choose_operation(operator, A->signal, B->signal);

    if(operation == 0)
        RES = subtracao(A, B);
    else if(operation == 1)
        RES = soma(A, B);
    else
        RES = multiplicacao(A, B);

    vectorint_print(RES);

    A = vectorint_free(A);
    B = vectorint_free(B);
    RES = vectorint_free(RES);

    // end = clock();
    // cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC / 1000000);
    // printf("\n\ntime: %.3fµs\n", cpu_time_used);
    return 0;
}