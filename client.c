#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#include "bignumber.h"

int main() {
    //clock_t start, end;
    //double cpu_time_used;
    //start = clock();

    VectorInt A, B, RES;
    char operator;

    char fim;
    while(fim != '.'){
        A = vectorint();
        B = vectorint();
        RES = vectorint();

        read_input(A);
        read_input(B);
        scanf("%c", &operator);

        switch (choose_operation(operator, A->signal, B->signal))
        {
        case 0:
            subtracao(A, B, RES);
            break;
        case 1:
            soma(A, B, RES);
            break;
        default:
            multiplicacao(A, B, RES);
            break;
        }

        vectorint_print(RES);
        //file_vectorint_print(RES, out);

        vectorint_free(A);
        vectorint_free(B);
        vectorint_free(RES);
        fim = getchar();
    }   

    //end = clock();
    //cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC / 1000);
    //printf("\n\ntime: %.3fms\n", cpu_time_used);
    return 0;
}
