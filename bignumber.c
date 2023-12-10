#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bignumber.h"

VectorInt vectorint(void) {
    VectorInt v = malloc(sizeof(vecint));
    v->data = malloc(sizeof(int8));
    v->nelements = 0;
    v->signal = 1;
    return v;
}

VectorInt vectorint_insert(VectorInt v, int8 a) {
    v->data = realloc(v->data, sizeof(int8) * (v->nelements+1));
    v->data[v->nelements] = a;
    v->nelements++;
    return v;
}

void vectorint_free(VectorInt v) {
    free(v->data);
    free(v);
}

void read_input(VectorInt A) {
    char temp = getchar();
    
    if (temp == 45) {  
        A->signal = -1;
        temp = (int)getchar();
    }
    while (temp != 10) {  
        A = vectorint_insert(A, temp - 48);  
        temp = (int)getchar();
    }
}

void file_read_input(VectorInt A, FILE* file) {
    char temp = fgetc(file);
    
    if (temp == 45) {  
        A->signal = -1;
        temp = (int)fgetc(file);
    }
    while (temp != 10) {  
        A = vectorint_insert(A, temp - 48);  
        temp = (int)fgetc(file);
    }
}

void reverse(VectorInt array) {
    int aux;
    int inicio = 0;
    int final = array->nelements - 1;

    while (inicio < final) {
        aux = array->data[inicio];
        array->data[inicio] = array->data[final];
        array->data[final] = aux;
        inicio++;
        final--;
    }
}

void filter_left_zero(VectorInt A) {
    int i = A->nelements - 1;

    while (A->data[i] == 0 && A->nelements > 1) {
        if (A->data[A->nelements - 1] == 0 && A->nelements != 1) A->nelements--;
        i--;
    }
}

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

void soma(VectorInt A, VectorInt B, VectorInt RES) {
    int i, up, tmp_sum, limit;

    up = 0;
    limit = max(A->nelements, B->nelements);

    reverse(A);
    reverse(B);

    for (i = 0; i < limit + 1; i++) {
        if (i >= A->nelements)
            vectorint_insert(A, 0);
        if (i >= B->nelements)
            vectorint_insert(B, 0);

        tmp_sum = A->data[i] + B->data[i] + up;
        vectorint_insert(RES, tmp_sum % 10);
        up = tmp_sum / 10;
    }

    if (RES->data[RES->nelements - 1] == 0)
        RES->nelements--;

    filter_left_zero(RES);
    RES->data[RES->nelements - 1] *= A->signal;
}

int compare(VectorInt A, VectorInt B) {
    int i;

    if (A->nelements > B->nelements)
        return 1;
    else if (A->nelements < B->nelements)
        return 2;
    else {
        for (i = 0; i < A->nelements; i++) {
            if (A->data[i] > B->data[i])
                return 1;
            else if (A->data[i] < B->data[i])
                return 2;
            else
                continue;
        }
    }

    return 0;
}

void subtracao(VectorInt A, VectorInt B, VectorInt RES) {
    VectorInt Maior;
    VectorInt Menor;

    int i, tmp_sub, limit, cmpr;
    cmpr = compare(A, B);

    if (cmpr == 1) {
        Maior = A;
        Menor = B;
    } else {
        Maior = B;
        Menor = A;
    }

    limit = Maior->nelements + 1;

    reverse(A);
    reverse(B);

    for (i = 0; i < limit; i++) {
        if (i < Maior->nelements)
            vectorint_insert(Maior, 0);

        if (i < Menor->nelements)
            vectorint_insert(Menor, 0);

        if (Maior->data[i] < Menor->data[i]) {
            Maior->data[i] += 10;
            Maior->data[i + 1]--;
        }

        tmp_sub = Maior->data[i] - Menor->data[i];

        vectorint_insert(RES, tmp_sub);
    }
    if (cmpr == 0)
        RES->nelements = 1;

    filter_left_zero(RES);

    if (Maior->signal == Menor->signal)
        RES->data[RES->nelements - 1] *= Maior->signal;
    if (A->signal == -1 && B->signal == 1)
        RES->data[RES->nelements - 1] *= -1;
    if (cmpr == 2)
        RES->data[RES->nelements - 1] *= -1;
}

void multiplicacao(VectorInt A, VectorInt B, VectorInt RES) {
    int i, j, tmp_mul, up;

    reverse(A);
    reverse(B);

    for (i = 0; i < A->nelements; i++) {
        up = 0;

        for (j = 0; j < B->nelements; j++) {
            if (i + j == RES->nelements)
                vectorint_insert(RES, 0);

            tmp_mul = A->data[i] * B->data[j] + up + RES->data[i + j];
            RES->data[i + j] = tmp_mul % 10;
            up = tmp_mul / 10;
        }
        while (up > 0) {
            vectorint_insert(RES, up % 10);
            up /= 10;
        }
    }
    filter_left_zero(RES);

    RES->signal = A->signal * B->signal;
    RES->data[RES->nelements - 1] *= RES->signal;
}

void vectorint_print(VectorInt X) {
    int i;
    for (i = X->nelements - 1; i >= 0; --i)
        printf("%d", (int)X->data[i]);
    printf("\n");
}

void file_vectorint_print(VectorInt X, FILE* out) {
    for (int i = X->nelements - 1; i >= 0; --i) fprintf(out,"%d", (int)X->data[i]);
    fprintf(out,"\n");
}

int choose_operation(char op, int signal_a, int signal_b) {
    if ((op == '+') && (signal_a == signal_b)) {
        return 1; // adicao
    } else if ((op == '+') && (signal_a != signal_b)) {
        return 0; // subtracao
    } else if ((op == '-') && (signal_a == signal_b)) {
        return 0; // subtracao
    } else if ((op == '-') && (signal_a != signal_b)) {
        return 1; // adicao
    } else {
        return 2; // multiplicacao
    }
}

char* nome_saida (const char* input){
    int n=5;
    for (int i=0; input[i] != '.' && input[i] != '\0';i++) n++;
    char* out = malloc(sizeof(char)*n);
    for (int i=0;i<n-5;i++) out[i] = input[i];
    out[n-5] = '.';
    out[n-4] = 'o';
    out[n-3] = 'u';
    out[n-2] = 't';
    out[n-1] = '\0';
    return out;
}



