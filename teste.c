#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <math.h>
#include <string.h>
//#include <stdint.h>
#define max_big 250

typedef struct {
    int* dig;
    short int n;
    short int head_index;
    size_t size;
} int1024;

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

//add input that represents max digits allowed with getvalue to choose real max
int1024* get_big(){
    Lista input = criar_lista();
    int1024* out = malloc(sizeof(int1024));
    out->n=0;

    while (1) {
        char temp = getchar();
        if (temp == '\n') break;
        Lista novo = malloc(sizeof(struct no));
        novo->dado = temp;
        novo->prox = input;
        input = novo;
        out->n++;
    } 
    printf("\nsize of struct: %d\n", (int)sizeof(int1024));
    printf("total chars read: %d\n",out->n);
    out->size = sizeof(int)*((out->n/9)+2);
    printf("allocating %d bytes\n", (int)out->size);
    out->dig = malloc(out->size);
    char* buffer = malloc(sizeof(char)*10);
    memset(buffer, '0', 9);
    buffer[9]='\0';
    signed char i = 8;
    short int index = 0;
    
    while (input != NULL) {
        buffer[i] = input->dado;
        Lista tmp = input;
        input = input->prox;
        free(tmp);

        if (((int)buffer[i] < 47 || 58 < (int)buffer[i]) && input!=NULL){out->n-=1; printf("typo detected: '%c'    n:%d\n",buffer[i],out->n); continue;}

        i--;
        if (i==-1 || input==NULL) {
            if (buffer[i+1] == '-') {buffer[i+1]='0';i=-2; printf("negative detected => i:%d\n",i);}
            sscanf(buffer, "%d", &out->dig[index]);
            //printf("index: %d    str: %s    value:%d\n",index,buffer,out->dig[index]);
            out->head_index=index;
            if (i==-2) out->dig[index]*=-1;
            memset(buffer, '0', 9);
            index++;
            i=8;
        } 
    }
    free(buffer);
    free(input);
    return out;
}


int main( ) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int1024* x = get_big();

    printf("head index: %d\n",x->head_index);
    printf("n of allocated indexes: %d\n\n",(int)x->size/4);
    for (int i=x->head_index;i>=0;i--){
        if(i==(int)(x->head_index)) {printf("%d",x->dig[i]); continue;}
        printf("%09d",x->dig[i]);
    }

    int* ptr = &x->dig[0];
    free(ptr);
    free(x);

    end = clock();
    cpu_time_used = ((double) (end - start)) / (CLOCKS_PER_SEC/1000);
    printf("\n\ntime: %.3fms\n", cpu_time_used);
    return 0;
}
