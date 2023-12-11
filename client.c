#include <stdio.h>
#include <stdlib.h>
#include "bignumber.h"
//#include <time.h>


int main(int argc, char* argv[]) {
    //clock_t start, end;
    //double cpu_time_used;
    //start = clock();

    BigNumber A, B, RES;
    char operator;

    FILE* file = fopen(argv[1], "r");

    if (argc != 2) {
        printf("Erro, sintaxe correta: %s filename\n", argv[0]);
        return 1;
    }

    if (file == NULL) {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    FILE* out; 
    char* output = file_name(argv[1]);
    out = fopen(output, "wr");
    

    while((operator = fgetc(file)) != EOF){
        ungetc(operator, file);

        A = bignumber();
        B = bignumber();
        RES = bignumber();

        read_input_file(A, file);
        read_input_file(B, file);
        fscanf(file, "%c\n", &operator);
        

        switch (choose_operation(operator, A->sign, B->sign))
        {
        case 0:
            subtract(A, B, RES);
            break;
        case 1:
            add(A, B, RES);
            break;
        default:
            multiply(A, B, RES);
            break;
        }

        bignumber_print_file(RES, out);

        bignumber_free(A);
        bignumber_free(B);
        bignumber_free(RES);
    }

    fclose(out);
    fclose(file);
    free(output);

    //end = clock();
    //cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC / 1000);
    //printf("time: %.3fms\n", cpu_time_used);
    return 0;
}
