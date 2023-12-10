#ifndef BIGNUMBER_H
#define BIGNUMBER_H

typedef signed char int8;
typedef struct {int8* data; int nelements; int signal;} vecint;
typedef vecint* VectorInt;

VectorInt vectorint(void);
VectorInt vectorint_insert(VectorInt v, int8 a);
void vectorint_free(VectorInt v);

void read_input(VectorInt A);
void file_read_input(VectorInt A, FILE* file);

void reverse(VectorInt array);
void filter_left_zero(VectorInt A);
int max(int a, int b);
int compare(VectorInt A, VectorInt B);

void soma(VectorInt A, VectorInt B, VectorInt RES);
void subtracao(VectorInt A, VectorInt B, VectorInt RES);
void multiplicacao(VectorInt A, VectorInt B, VectorInt RES);

void vectorint_print(VectorInt X);
void file_vectorint_print(VectorInt X, FILE* out);
int choose_operation(char op, int signal_a, int signal_b);

#endif
