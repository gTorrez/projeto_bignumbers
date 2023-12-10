#ifndef BIGNUMBER_H
#define BIGNUMBER_H

typedef signed char int8;
typedef struct {int8* data; int nelements; int sign;} bignum;
typedef bignum* BigNumber;

BigNumber bignumber(void);
void bignumber_insert(BigNumber A, int8 a);
void bignumber_free(BigNumber A);

void read_input(BigNumber A);
void read_input_file(BigNumber A, FILE* file);

void reverse(BigNumber A);
void filter_left_zero(BigNumber A);
int max(int a, int b);
int compare(BigNumber A, BigNumber B);

void add(BigNumber A, BigNumber B, BigNumber RES);
void subtract(BigNumber A, BigNumber B, BigNumber RES);
void multiply(BigNumber A, BigNumber B, BigNumber RES);

void bignumber_print(BigNumber A);
void bignumber_print_file(BigNumber A, FILE* out);
int choose_operation(char op, int signal_a, int signal_b);
char* file_name(const char* input);

#endif
