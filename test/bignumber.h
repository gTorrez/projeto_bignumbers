#ifndef BIGNUMBER_H
#define BIGNUMBER_H

typedef struct {int *data; int nelements; int capacity; int signal;}* VectorInt;

VectorInt vectorint(void);
VectorInt read_input(void);
VectorInt vectorint_insert(VectorInt v, int a);
void vectorint_print(VectorInt X);
VectorInt vectorint_free(VectorInt v);

VectorInt reverse(VectorInt array);
VectorInt filter_left_zero(VectorInt A);
int compare(VectorInt A, VectorInt B);

VectorInt soma(VectorInt A, VectorInt B);
VectorInt subtracao(VectorInt A, VectorInt B);
VectorInt multiplicacao(VectorInt A, VectorInt B);

int choose_operation(char op, int signal_a, int signal_b);
int max(int a, int b);

#endif
