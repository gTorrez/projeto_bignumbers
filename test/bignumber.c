#include <stdio.h>
#include <stdlib.h>
#include "bignumber.h"

VectorInt vectorint(void) {
    VectorInt v = malloc(sizeof(struct{
                        int* data;
                        int capacity; 
                        int nelements; 
                        int signal;
                        }));
    
    v->data = malloc(sizeof(int));
    v->capacity = 1;
    v->nelements = 0;
    v->signal = 1;
    return v;
}

VectorInt vectorint_insert(VectorInt v, int a) {
    if (v->nelements == v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, sizeof(int) * v->capacity);
    }

    v->data[v->nelements] = a;
    v->nelements += 1;

    return v;
}

VectorInt vectorint_free(VectorInt v) {
    free(v->data);
    free(v);
    return NULL;
}

VectorInt read_input(void) {
    VectorInt A = vectorint();
    int temp, count, check;
    count = 0;
    check = 0;

    while (1) {
        temp = getchar();

        if (temp == 45)
            check = -1;

        if (temp == 10)
            break;

        if (temp != 45) {
            A = vectorint_insert(A, temp - 48);
            count += 1;
        }
    }
    A->nelements = count;
    if (check == -1) A->signal = -1;

    return A;
}

VectorInt reverse(VectorInt array) {
    int aux;
    int inicio = 0;
    int final = array->nelements - 1;

    while (inicio < final) {
        aux = array->data[inicio];
        array->data[inicio] = array->data[final];
        array->data[final] = aux;
        inicio += 1;
        final -= 1;
    }

    return array;
}

int max(int a, int b){
    if(a > b)
        return a;
    
    return b;
}

VectorInt soma(VectorInt A, VectorInt B) {
    int i, up, tmp_sum, limit;

    VectorInt RES = vectorint();

    up = 0;
    limit = max(A->nelements, B->nelements);

    A = reverse(A);
    B = reverse(B);

    for (i = 0; i < limit + 1; i++) {
        if (i >= A->nelements) A = vectorint_insert(A, 0);
        if (i >= B->nelements) B = vectorint_insert(B, 0);

        tmp_sum = A->data[i] + B->data[i] + up;
        RES = vectorint_insert(RES, tmp_sum % 10);
        up = tmp_sum / 10;
    }

    if (RES->data[RES->nelements - 1] == 0) 
        RES->nelements--;

    RES->data[RES->nelements - 1] *= A->signal;

    return RES;
}


int compare(VectorInt A, VectorInt B) {
    int i;

    if (A->nelements > B->nelements)
        return 1;

    else if (A->nelements < B->nelements)
        return 2;

    else {
        for(i=0; i<A->nelements; i++){
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

VectorInt filter_left_zero(VectorInt A) {
    int i = A->nelements - 1;
    //printf("nelements: %d\n", A->nelements);
    while (A->data[i] != A->data[0]) {
        //printf("limpa zero: %d\n", A->data[i]);
        if (A->data[A->nelements - 1] == 0 && A->nelements != 1)
            A->nelements -= 1;

        i -= 1;
    }
    return A;
}

VectorInt subtracao(VectorInt A, VectorInt B) {
    VectorInt Maior;
    VectorInt Menor;
    VectorInt RES = vectorint();
    int i, tmp_sub, limit, cmpr;
    cmpr = compare(A, B);

    if (cmpr == 1) {
        Maior = A;
        Menor = B;
    } 

    else {
        Maior = B;
        Menor = A;
    }

    limit = Maior->nelements + 1;

    A = reverse(A);
    B = reverse(B);

    for (i = 0; i < limit; i++) {
        if (i < Maior->nelements)
            Maior = vectorint_insert(Maior, 0);

        if (i < Menor->nelements)
            Menor = vectorint_insert(Menor, 0);

        if (Maior->data[i] < Menor->data[i]) {
            Maior->data[i] += 10;
            Maior->data[i + 1] -= 1;
        }

        tmp_sub = Maior->data[i] - Menor->data[i];

        RES = vectorint_insert(RES, tmp_sub);
    }
    if(cmpr == 0) RES->nelements = 1;

    RES = filter_left_zero(RES);

    if (Maior->signal == Menor->signal) RES->data[RES->nelements - 1] *= Maior->signal;
    if (A->signal == -1 && B->signal == 1) RES->data[RES->nelements - 1] *= -1;
    if (cmpr == 2) RES->data[RES->nelements - 1] *= -1;
    
    return RES;
}

VectorInt multiplicacao(VectorInt A, VectorInt B) {
    int i, j, tmp_mul, up;
    VectorInt RES = vectorint();
    A = reverse(A);
    B = reverse(B);

    for (i = 0; i < A->nelements; i++) {
        up = 0;

        for (j = 0; j < B->nelements; j++) {
            if (i + j == RES->nelements) {
                RES = vectorint_insert(RES, 0);
            }
            tmp_mul = A->data[i] * B->data[j] + up + RES->data[i + j];
            RES->data[i + j] = tmp_mul % 10;
            up = tmp_mul / 10;
        }
        while (up > 0) {
            RES = vectorint_insert(RES, up % 10);
            up /= 10;
        }
    }
    RES->signal = A->signal * B->signal;
    RES->data[RES->nelements-1] *= RES->signal;

    filter_left_zero(RES);
    return RES;
}

void vectorint_print(VectorInt X) {
    int i;
    for (i = X->nelements - 1; i >= 0; --i) 
        printf("%d", X->data[i]);
}


int choose_operation(char op, int signal_a, int signal_b){
    if((op == '+') && (signal_a == signal_b)){
        return 1; // adicao
    }
    else if((op == '+') && (signal_a != signal_b)){
        return 0; // subtracao
    }
    else if((op == '-') && (signal_a == signal_b)){
        return 0; // subtracao
    }
    else if((op == '-') && (signal_a != signal_b)){
        return 1; // adicao
    }
    else{
        return 2; // multiplicacao
    }
}