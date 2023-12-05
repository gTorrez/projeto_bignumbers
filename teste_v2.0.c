#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#define max_n 4000

typedef struct {
    int32_t* dig;
    uint16_t head_index;
    size_t size;
    char sign;
} dyn_int;

typedef struct no* Lista;
struct no {
    char dado;
    Lista prox;
};

Lista criar_lista() {
    return NULL;
}

int get_valid(int max, char s[]) {
    int n;
    if(max==0){
        printf("Input %s value: ", s);
        scanf("%d", &n);
        while ((getchar()) != '\n');
        return n;
    }
    printf("Input %s up to %d: ", s, max);
    while (1) {
        scanf("%d", &n);
        while ((getchar()) != '\n');
        if (n <= max && n > 0) break;
        printf("Invalid input, try again: ");
    }
    return n;
}

void print_int(dyn_int* x){
    printf("Size (bytes): %4d     |  Allocated indexes: %3d  |  Head: %3d\n\n",(int)(x->size+sizeof(dyn_int)), (int)(x->size/sizeof(int32_t)),x->head_index);
    for (short int i=x->head_index;i>=0;i--){
        if(i==(int)(x->head_index)) {printf("%c",x->sign);printf("%d ",x->dig[i]); continue;}
        printf("%09d ",x->dig[i]);
    }
    printf("\n\n");
}

void free_int(dyn_int* x){
    int32_t* ptr = &x->dig[0];
    free(ptr);
    free(x);
}


void switch_sign(dyn_int* x){
    for (int i=0;i<=x->head_index;i++) x->dig[i] *= -1; 
}

dyn_int* sum(dyn_int* a,dyn_int* b){
    dyn_int* sum = malloc(sizeof(dyn_int));
    int8_t sA = 1;
    int8_t sB = 1;
    int8_t carry = 0;

    if(a->head_index > b->head_index) {
        sum->head_index = a->head_index+1;
        sum->sign = a->sign;
        if (a->sign != b->sign) sB = -1;           
    }
    else if(a->head_index < b->head_index){
        sum->head_index = b->head_index+1;
        sum->sign = b->sign;
        if (a->sign != b->sign) sA = -1;       
    }  
    else{
        sum->head_index = a->head_index+1;
        if (a->sign == b->sign) sum->sign = a->sign;
        else{for(short int i = sum->head_index; i>=0;i--) {
                if(a->dig[i] > b->dig[i]) {sB = -1; sum->sign = a->sign; break;}
                if(a->dig[i] < b->dig[i]) {sA = -1; sum->sign = b->sign; break;}
                if (i==0) {
                    sum->size = sizeof(int32_t);
                    sum->dig = malloc(sum->size);
                    sum->dig[0] = 0;
                    sum->head_index = 0;
                    sum->sign = '\0';
                    return sum;
    }   }   }   }
    sum->size = (size_t)((sum->head_index)*sizeof(int32_t));
    sum->dig = malloc(sum->size);
    printf("Allocating %d bytes for sum  |  signA: %d  |  signB: %d  |  signSum: %c\n", (int)sum->size,sA,sB,sum->sign);

    for (short int i = 0; i<=sum->head_index; i++){     
        sum->dig[i] = (a->dig[i] * sA * !(i>a->head_index)) + ((b->dig[i]) * sB * !(i>b->head_index)) + carry;
        if(sum->dig[i]<0){
            sum->dig[i] += 1000000000;
            carry = -1;
        }
        else if (sum->dig[i]>999999999){
            sum->dig[i] -= 1000000000; 
            carry = 1;
        } 
        else carry = 0;
        //printf("Index=[%d]   |   A: %010d   |   B: %010d   |   Sum: %010d   |   Carry: %d \n",i,a->dig[i],b->dig[i],sum->dig[i],carry);
    }
    while (sum->dig[sum->head_index]==0 && sum->head_index>0) {
        //int32_t* ptr = &sum->dig[sum->head_index];
        //free(ptr);
        sum->head_index--;
    }
    //sum->size = (size_t)((sum->head_index)*sizeof(int32_t));
    return sum;
}

dyn_int* sub(dyn_int* a,dyn_int* b){
    if (b->sign=='\0') b->sign = '-';
    else  b->sign='\0';
    return sum(a,b);
}

dyn_int* mult(dyn_int* a,dyn_int* b){
    dyn_int* result = malloc(sizeof(dyn_int));
    result->size = (size_t)(sizeof(int32_t)*(a->head_index+b->head_index+1));
    result->dig = malloc(result->size);
    if (b->sign == a->sign) result->sign= '\0';
    else  result->sign= '-';

    if(a->head_index > b->head_index) {

    }
    else {}



    return NULL;
}



dyn_int* get_big(){
    Lista input = criar_lista();
    dyn_int* out = malloc(sizeof(dyn_int));
    uint16_t n = 0;

    while(1) {
        char temp = getchar();
        if (temp == '\n') break;
        Lista novo = malloc(sizeof(struct no));
        novo->dado = temp;
        novo->prox = input;
        input = novo;
        n++;
    }
    if (n>max_n){printf("Too many digits! Exiting\n");return NULL;}

    out->size = (size_t)sizeof(int32_t)*(((n-1)/9)+1);
    out->dig = malloc(out->size);
    out->sign = '\0';
    char* buffer = malloc(sizeof(char)*10);
    memset(buffer, '0', 9);
    buffer[9]='\0';
    int8_t i = 8;
    uint16_t index = 0;
    
    printf("Total chars read: %4d |  Allocating %4d bytes   |  ",n, (int)out->size);

    while (input != NULL) {
        buffer[i] = input->dado;
        Lista tmp = input;
        input = input->prox;
        free(tmp);
        if (((int)buffer[i] < 47 || 58 < (int)buffer[i]) && input!=NULL){n-=1; continue;}
        i--;
        if (i==-1 || input==NULL) {
            if (buffer[i+1] == '-') {buffer[i+1]='0';out->sign='-'; printf("Negative Detected!  |  ");}
            sscanf(buffer, "%d", &out->dig[index]);
            out->head_index=index;
            memset(buffer, '0', 9);
            index++;
            i=8;
        } 
    }

    if (out->dig[out->head_index]==0) out->head_index--;
    printf("Digits: %4d\n",n);
    free(buffer);
    free(input);
    return out;
}

int main( ) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    printf("Size of struct: %d bytes, input is dynamically allocated  |  Input number up to %d digits:\n", (int)sizeof(dyn_int), max_n);

    dyn_int* A = get_big();
    if(A==NULL) return 1;
    print_int(A);

    dyn_int* B = get_big();
    if(B==NULL) return 1;
    print_int(B);

    dyn_int* C = sum(A,B);
    print_int(C);

    free_int(A);
    free_int(B);
    free_int(C);

    end = clock();
    cpu_time_used = ((double) (end - start)) / (CLOCKS_PER_SEC/1000);
    printf("\n\ntime: %.3fms\n", cpu_time_used);
    return 0;
}
