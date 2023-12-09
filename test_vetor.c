#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int capacity; // capacidade do 'array' data
    int nelements; // número de elementos guardados em data
    int signal;
}*VectorInt;


VectorInt vectorint(void){
    VectorInt v;
    v = malloc(sizeof(struct{
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


void vectorint_insert(VectorInt v, int a){
    if(v->nelements == v->capacity){
        v->capacity *= 2;
        v->data = realloc(v->data, sizeof(int) * v->capacity);
    }

    v->data[v->nelements] = a;
    v->nelements += 1;
}



void vectorint_free(VectorInt v){
    free(v->data);
    free(v);
}


void read_input(VectorInt* A){
    int temp, count, check;

    count = 0; 
    check = 0;

    while(1){
        temp = getchar();

        if(temp == 45)
            check = -1;
        
        if(temp == 10)
            break;

        if(temp != 45){
            vectorint_insert((*A), temp-48);
            count += 1;
        }
    }
    
    (*A)->nelements = count;

    if(check == -1)
        (*A)->signal = -1;    
}


void reverse(int* array, int inicio, int final){
    int aux;
    
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


void soma(VectorInt* A, VectorInt* B, VectorInt* RES){
    int i, up, tmp_sum, limit;
 
    up = 0;
    limit = max((*A)->nelements, (*B)->nelements);

    reverse((*A)->data, 0, (*A)->nelements-1);
    reverse((*B)->data, 0, (*B)->nelements-1);

    for(i=0; i<limit+1; i++){
        if(i >= (*A)->nelements)
            vectorint_insert((*A), 0);

        if(i >= (*B)->nelements)
            vectorint_insert((*B), 0);

        tmp_sum = (*A)->data[i] + (*B)->data[i] + up;

        vectorint_insert((*RES), tmp_sum % 10);

        up = tmp_sum/10;
    }

    if((*RES)->data[(*RES)->nelements-1] == 0)
        (*RES)->nelements -= 1;
    

    (*RES)->data[(*RES)->nelements-1] *= (*A)->signal;
}


int compare(VectorInt* A, VectorInt* B, int i){
    if((*A)->nelements > (*B)->nelements)
        return 1;
    
    else if((*A)->nelements < (*B)->nelements)
        return 2;

    else{
        //printf("A: %d, B: %d\n", (*A)->data[i], (*B)->data[i]);
        if((*A)->data[i] > (*B)->data[i])
            return 1;
        
        else if((*A)->data[i] < (*B)->data[i])
            return 2;

        else 
            return compare(A, B, i+1);
    }
}


void filter_left_zero(VectorInt* A){
    int i;

    i = (*A)->nelements-1;
    while((*A)->data[i] == 0){
        if((*A)->data[(*A)->nelements-1] == 0 && (*A)->nelements != 1)
            (*A)->nelements -= 1;

        i -= 1;
    }
}


void subtracao(VectorInt* A, VectorInt* B, VectorInt* RES){
    VectorInt* Maior; 
    VectorInt* Menor;
    int i, tmp_sub, limit, cmpr;
    
    cmpr = compare(A, B, 0);

    if(cmpr == 1){
        Maior = A;
        Menor = B;
    }
    else{
        Maior = B;
        Menor = A;
    }

    //printf("maior: %d\n", cmpr);
    limit = (*Maior)->nelements+1;

    reverse((*A)->data, 0, (*A)->nelements-1);
    reverse((*B)->data, 0, (*B)->nelements-1);

    for(i=0; i < limit; i++){
        if(i < (*Maior)->nelements)
            vectorint_insert((*Maior), 0);

        if(i < (*Menor)->nelements)
            vectorint_insert((*Menor), 0);
        
        if((*Maior)->data[i] < (*Menor)->data[i]){
            (*Maior)->data[i] += 10;
            (*Maior)->data[i+1] -= 1;
        }

        tmp_sub = (*Maior)->data[i] - (*Menor)->data[i];

        vectorint_insert((*RES), tmp_sub);
    }

    filter_left_zero(RES);

    if((*Maior)->signal == (*Menor)->signal)
        (*RES)->data[(*RES)->nelements-1] *= (*Maior)->signal;

    if(cmpr == 2)
        (*RES)->data[(*RES)->nelements-1] *= -1;
}


void vectorint_print(VectorInt* X){
    int i;

    for(i = (*X)->nelements-1; i>=0 ; --i)
        printf("%d", (*X)->data[i]);
}



int main(){
    VectorInt A, B, RES;

    A = vectorint();
    B = vectorint();
    RES = vectorint();

    read_input(&A);
    read_input(&B);

    subtracao(&A, &B, &RES);
    
    vectorint_print(&RES);
    
    vectorint_free(A);
    vectorint_free(B);
    vectorint_free(RES);

    return 0;
}