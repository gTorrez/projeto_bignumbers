#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bignumber.h"

int main(int argc, char* argv[]) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    VectorInt A, B, RES;
    char operator;

    FILE* arquivo = fopen(argv[1], "r");

    if (argc != 2) {
        printf("Erro, sintaxe correta: %s filename\n", argv[0]);
        return 1;
    }

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    FILE* out; 
    char* output = nome_saida(argv[1]);
    out = fopen(output, "wr");
    

    while((operator = fgetc(arquivo)) != EOF){
        ungetc(operator, arquivo);

        A = vectorint();
        B = vectorint();
        RES = vectorint();

        file_read_input(A,arquivo);
        file_read_input(B,arquivo);
        fscanf(arquivo,"%c\n", &operator);
        

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

        file_vectorint_print(RES, out);

        vectorint_free(A);
        vectorint_free(B);
        vectorint_free(RES);
    }

    fclose(out);
    fclose(arquivo);
    free(output);


    end = clock();
    cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC / 1000);
    printf("time: %.3fms\n", cpu_time_used);
    return 0;
}
