#ifndef BIGNUMBER_H
#define BIGNUMBER_H

typedef struct {int *data; int nelements; int capacity; int signal;}* VectorInt;

VectorInt vectorint(void);
void read_input(VectorInt* A);
VectorInt vectorint_insert(VectorInt v, int a);
void vectorint_print(VectorInt* X);
void vectorint_free(VectorInt* v);

void reverse(VectorInt* array);
void filter_left_zero(VectorInt* A);
int compare(VectorInt* A, VectorInt* B);

void soma(VectorInt* A, VectorInt* B, VectorInt* RES);
void subtracao(VectorInt* A, VectorInt* B, VectorInt* RES);
void multiplicacao(VectorInt* A, VectorInt* B, VectorInt* RES);

int choose_operation(char op, int signal_a, int signal_b);
int max(int a, int b);

#endif
