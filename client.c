#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct{
    char number[MAX];
    int signal;
    int n_elements;
}BigNumber;


int char_to_int(char c){
    return c - 48;
}


void map(char* array, int n, int func(char)){
    int i;

    for(i=0; i<n; i++)
        if(array[i] != '\n')
            array[i] = func(array[i]);
}


void print_bignum(char* array, int n){
    int i;

    for(i=0; i<n; i++)
        printf("%d", array[i]);
    printf("\n");

}


void reverse(char* array, int inicio, int final){
    char aux;
    
    if(inicio >= final)
        return;
    
    aux = array[inicio];
    array[inicio] = array[final];
    array[final] = aux;

    return reverse(array, inicio+1, final-1);
}


int max(int a, int b){
    if(a > b)
        return a;
    
    return b;
}


BigNumber soma(BigNumber A, BigNumber B, BigNumber RES){
    int i, up, tmp_sum;

    up = 0;
    for(i=0; i<RES.n_elements; i++){
        if(i >= A.n_elements)
            A.number[i] = 0;

        if(i >= B.n_elements)
            B.number[i] = 0;

        tmp_sum = A.number[i] + B.number[i] + up;
        RES.number[i] = tmp_sum % 10;

        up = tmp_sum/10;
    }

    if(RES.number[RES.n_elements-1] == 0)
        RES.n_elements -= 1;

    return RES;
}


BigNumber subtracao(BigNumber A, BigNumber B, BigNumber RES){
    int i, down, tmp_sub;

    down = 0;
    for(i=0; i<RES.n_elements; i++){
        if(i >= A.n_elements)
            A.number[i] = 0;

        if(i >= B.n_elements)
            B.number[i] = 0;
 
        if(A.number[i] < B.number[i]){
            A.number[i] += 10;
            A.number[i+1] -= 1; 
        }

        tmp_sub = A.number[i] - B.number[i];
        RES.number[i] = tmp_sub;

    }

    if(RES.number[RES.n_elements-1] == 0 && RES.n_elements != 1)
        RES.n_elements -= 1;

    return RES;
}


int choose_operation(char op, int signal_a, int signal_b){
    if((op == '+') && (signal_a == signal_b))
        return 1; // adicao
    else if((op == '+') && (signal_a != signal_b))
        return 0; // subtracao
    else if((op == '-') && (signal_a == signal_b))
        return 0; // subtracao
    else if((op == '-') && (signal_a != signal_b))
        return 1; // adicao
}


int main(){
    int i, operation;
    char operator;
    BigNumber A, B, RES;

    fgets(A.number, MAX, stdin);
    fgets(B.number, MAX, stdin);
    scanf("%c", &operator);

    A.n_elements = strlen(A.number)-1;
    B.n_elements = strlen(B.number)-1;

    // if(A.number[0] == '-'){
    //     A.signal = -1;
    //     A.number[0] = 0;
    //     A.n_elements -= 1;
    // }
    // else
    //     A.signal = 1;
    
    // if(B.number[0] == '-'){
    //     B.signal = -1;
    //     B.number[0] = 0;
    //     B.n_elements -= 1;
    // }
    // else
    //     B.signal = 1;
    

    if(A.n_elements - B.n_elements >= 2)
        RES.n_elements = A.n_elements + 1;
    else
        RES.n_elements = B.n_elements + 1;
   
    map(A.number, A.n_elements, char_to_int);
    map(B.number, B.n_elements, char_to_int);

    reverse(A.number, 0, A.n_elements-1);
    reverse(B.number, 0, B.n_elements-1);

    //operation = choose_operation(operator, A.signal, B.signal);
    if(operator == '+')
        RES = soma(A, B, RES);
    else if(operator == '-')
        RES = subtracao(A, B, RES);
    else if(operator == '*')
        printf("Nao ta implementado ainda kkkkk");
    else
        printf("Operacao nao identificada.");

    reverse(RES.number, 0, RES.n_elements-1);
    
    print_bignum(RES.number, RES.n_elements);

    return 0;
}