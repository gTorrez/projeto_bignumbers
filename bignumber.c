#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bignumber.h"

// cria um bignumber (representado por um vetor dinâmico)
BigNumber bignumber(void) {
    BigNumber v = malloc(sizeof(bignum));
    v->data = malloc(sizeof(int8));
    v->nelements = 0;
    v->sign = 1;
    return v;
}

// insere elemento no bignumber
void bignumber_insert(BigNumber A, int8 a) {
    A->data = realloc(A->data, sizeof(int8) * (A->nelements+1));
    A->data[A->nelements] = a;
    A->nelements++;
}

// libera memória alocada para o bignumber
void bignumber_free(BigNumber A) {
    free(A->data);
    free(A);
}

// le input do usuário (terminal)
void read_input(BigNumber A) {
    char temp = getchar();
    
    if (temp == 45) {  
        A->sign = -1;
        temp = (int)getchar();
    }
    while (temp != 10) {  
        bignumber_insert(A, temp - 48);  
        temp = (int)getchar();
    }
}

// le input do usuário (arquivo)
void read_input_file(BigNumber A, FILE* file) {
    char temp = fgetc(file);
    
    if (temp == 45) {  
        A->sign = -1;
        temp = (int)fgetc(file);
    }
    while (temp != 10) {  
        bignumber_insert(A, temp - 48);  
        temp = (int)fgetc(file);
    }
}

// inverte o bignumber para realização das operações
void reverse(BigNumber A) {
    int aux;
    int inicio = 0;
    int final = A->nelements - 1;

    while (inicio < final) {
        aux = A->data[inicio];
        A->data[inicio] = A->data[final];
        A->data[final] = aux;
        inicio++;
        final--;
    }
}

// filtra os zeros à esquerda
void filter_left_zero(BigNumber A) {
    int i = A->nelements - 1;

    while (A->data[i] == 0 && A->nelements > 1) {
        if (A->data[A->nelements - 1] == 0 && A->nelements != 1) A->nelements--;
        i--;
    }
}

// retorna o maior numero entre dois inteiros
int max(int a, int b) {
    if (a > b) return a;
    return b;
}

// soma os bignumbers
void add(BigNumber A, BigNumber B, BigNumber RES) {
    int i, up, tmp_sum, limit;

    up = 0;
    limit = max(A->nelements, B->nelements);

    reverse(A);
    reverse(B);

    for (i = 0; i < limit + 1; i++) {
        if (i >= A->nelements)
            bignumber_insert(A, 0);
        if (i >= B->nelements)
            bignumber_insert(B, 0);

        tmp_sum = A->data[i] + B->data[i] + up;
        bignumber_insert(RES, tmp_sum % 10);
        up = tmp_sum / 10;
    }

    if (RES->data[RES->nelements - 1] == 0)
        RES->nelements--;

    filter_left_zero(RES);
    RES->data[RES->nelements - 1] *= A->sign;
}

// compara dois bignumbers e retorna qual o maior
// se o A for maior, retorna 1; se B for maior, retorna 2, se forem iguais retorna 0
int compare(BigNumber A, BigNumber B) {
    int i;

    if (A->nelements > B->nelements)
        return 1;
    else if (A->nelements < B->nelements)
        return 2;
    else {
        for (i = A->nelements-1; i >= 0; i--) {
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

// subtração de dois bignumbers
void subtract(BigNumber A, BigNumber B, BigNumber RES) {
    BigNumber Higher;
    BigNumber Lower;

    int i, tmp_sub, limit, cmpr;

    reverse(A);
    reverse(B);

    filter_left_zero(A);
    filter_left_zero(B);

    cmpr = compare(A, B);

    if (cmpr == 1) {
        Higher = A;
        Lower = B;
    } else {
        Higher = B;
        Lower = A;
    }

    limit = Higher->nelements + 1;

    for (i = 0; i < limit; i++) {
        if (i < Higher->nelements)
            bignumber_insert(Higher, 0);

        if (i < Lower->nelements)
            bignumber_insert(Lower, 0);

        if (Higher->data[i] < Lower->data[i]) {
            Higher->data[i] += 10;
            Higher->data[i + 1]--;
        }

        tmp_sub = Higher->data[i] - Lower->data[i];

        bignumber_insert(RES, tmp_sub);
    }
    if (cmpr == 0)
        RES->nelements = 1;

    filter_left_zero(RES);

    if (Higher->sign == Lower->sign)
        RES->data[RES->nelements - 1] *= Higher->sign;
    if (A->sign == -1 && B->sign == 1)
        RES->data[RES->nelements - 1] *= -1;
    if (cmpr == 2)
        RES->data[RES->nelements - 1] *= -1;
}

// multiplicação de dois big numbers
void multiply(BigNumber A, BigNumber B, BigNumber RES) {
    int i, j, tmp_mul, up;

    reverse(A);
    reverse(B);

    for (i = 0; i < A->nelements; i++) {
        up = 0;

        for (j = 0; j < B->nelements; j++) {
            if (i + j == RES->nelements)
                bignumber_insert(RES, 0);

            tmp_mul = A->data[i] * B->data[j] + up + RES->data[i + j];
            RES->data[i + j] = tmp_mul % 10;
            up = tmp_mul / 10;
        }
        while (up > 0) {
            bignumber_insert(RES, up % 10);
            up /= 10;
        }
    }
    filter_left_zero(RES);

    RES->sign = A->sign * B->sign;
    RES->data[RES->nelements - 1] *= RES->sign;
}

// printa no terminal um bignumber
void bignumber_print(BigNumber A) {
    int i;
    for (i = A->nelements - 1; i >= 0; --i)
        printf("%d", (int)A->data[i]);
    printf("\n");
}

// escreve o bignumber em um arquivo
void bignumber_print_file(BigNumber A, FILE* out) {
    for (int i = A->nelements - 1; i >= 0; --i) fprintf(out,"%d", (int)A->data[i]);
    fprintf(out,"\n");
}

// avalia qual operação deve ser executada de acordo com a combinação 
// dos sinais dos números e do operador
int choose_operation(char op, int sign_a, int sign_b) {
    if ((op == '+') && (sign_a == sign_b)) {
        return 1; // adicao
    } else if ((op == '+') && (sign_a != sign_b)) {
        return 0; // subtracao
    } else if ((op == '-') && (sign_a == sign_b)) {
        return 0; // subtracao
    } else if ((op == '-') && (sign_a != sign_b)) {
        return 1; // adicao
    } else {
        return 2; // multiplicacao
    }
}

// atribui nome ao arquivo de saida
char* file_name(const char* input){
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

