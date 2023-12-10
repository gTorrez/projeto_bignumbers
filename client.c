#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#include "bignumber.h"

int main(int argc){
    // clock_t start, end;
    // double cpu_time_used;
    // start = clock();

    VectorInt A, B, RES;
    int operation;
    char operator;

    A = vectorint();
    B = vectorint();
    RES = vectorint();

    read_input(&A);
    read_input(&B);
    scanf("%c", &operator);

    operation = choose_operation(operator, A->signal, B->signal);

    if(operation == 0)
        subtracao(&A, &B, &RES);
    else if(operation == 1)
        soma(&A, &B, &RES);
    else
        multiplicacao(&A, &B, &RES);

    vectorint_print(&RES);

    vectorint_free(&A);
    vectorint_free(&B);
    vectorint_free(&RES);

    // end = clock();
    // cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC / 1000000);
    // printf("\n\ntime: %.3fµs\n", cpu_time_used);
    return 0;
}