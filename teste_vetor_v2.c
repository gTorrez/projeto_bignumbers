#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int *data;
    int capacity; // capacidade do 'array' data
    int nelements; // número de elementos guardados em data
    int signal;
}* VectorInt;

VectorInt vectorint(void) {
    VectorInt v = malloc(sizeof(VectorInt));
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

VectorInt soma(VectorInt A, VectorInt B) {
    int i, up, tmp_sum, limit;

    VectorInt RES = vectorint();

    up = 0;
    limit = (A->nelements)*(A->nelements>B->nelements)+(B->nelements)*(A->nelements<B->nelements);

    A = reverse(A);
    B = reverse(B);

    for (i = 0; i < limit + 1; i++) {
        if (i >= A->nelements) A = vectorint_insert(A, 0);
        if (i >= B->nelements) B = vectorint_insert(B, 0);

        tmp_sum = A->data[i] + B->data[i] + up;
        RES = vectorint_insert(RES, tmp_sum % 10);
        up = tmp_sum / 10;
    }

    if (RES->data[RES->nelements - 1] == 0) RES->nelements--;
    RES->data[RES->nelements - 1] *= A->signal;

    return reverse(RES);
}

int compare(VectorInt A, VectorInt B, int i) {
    if (A->nelements > B->nelements)
        return 1;
    else if (A->nelements < B->nelements)
        return 2;
    else {
        if (A->data[i] > B->data[i])
            return 1;
        else if (A->data[i] < B->data[i])
            return 2;
        else
            return compare(A, B, i + 1);
    }
}

VectorInt filter_left_zero(VectorInt A) {
    int i = A->nelements - 1;
    while (A->data[i] == 0) {
        if (A->data[A->nelements - 1] == 0 && A->nelements != 1)
            A->nelements -= 1;

        i -= 1;
    }

    return A;
}

VectorInt subtracao(VectorInt A, VectorInt B) {
    VectorInt Maior;
    VectorInt Menor;
    int i, tmp_sub, limit, cmpr;
    cmpr = compare(A, B, 0);

    if (cmpr == 1) {
        Maior = A;
        Menor = B;
    } else {
        Maior = B;
        Menor = A;
    }
    limit = Maior->nelements + 1;

    A = reverse(A);
    B = reverse(B);
    VectorInt RES = vectorint();

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
    RES = filter_left_zero(RES);

    if (Maior->signal == Menor->signal) RES->data[RES->nelements - 1] *= Maior->signal;
    if (cmpr == 2) RES->data[RES->nelements - 1] *= -1;

    return reverse(RES);
}

VectorInt multiplicacao(VectorInt A, VectorInt B) {
    int i, j, tmp_mul, up;
    VectorInt temp = vectorint();
    A = reverse(A);
    B = reverse(B);

    for (i = 0; i < A->nelements; i++) {
        up = 0;

        for (j = 0; j < B->nelements; j++) {
            if (i + j == temp->nelements) {
                temp = vectorint_insert(temp, 0);
            }
            tmp_mul = A->data[i] * B->data[j] + up + temp->data[i + j];
            temp->data[i + j] = tmp_mul % 10;
            up = tmp_mul / 10;
        }
        while (up > 0) {
            temp = vectorint_insert(temp, up % 10);
            up /= 10;
        }
    }
    temp->signal = A->signal * B->signal;

    return filter_left_zero(temp);
}

void vectorint_print(VectorInt X) {
    int i;
    for (i = X->nelements - 1; i >= 0; --i) printf("%d", X->data[i]);
}

int main() {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    VectorInt A, B, RES;

    A = read_input();
    B = read_input();

    RES = multiplicacao(A, B);

    vectorint_print(RES);

    A = vectorint_free(A);
    B = vectorint_free(B);
    RES = vectorint_free(RES);

    end = clock();
    cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC / 1000000);
    printf("\n\ntime: %.3fµs\n", cpu_time_used);
    return 0;
}
