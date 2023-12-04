#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
//#include <string.h>
#include <stdint.h>
//#define max_char 2466 //log10((2^32)^256)
#define max_big 256
#define log2_max_big 8
#define i32size 4294967296

typedef struct {
    uint_32_t dig[max_big];
    //KB big (2^32)^255 = 10e2465
    // uint32_t: Exactly 32 bits (4 bytes), range from 0 to 4,294,967,295
} bigint;


bigint get_big(){
    bigint x;
    uint_fast16_t i = 0 ;
    scanf("%19d",&tq);
    x.dig[i+1] = x.[]/i32size;
    x.dig[max_big-1]
    if ();


}

int main( ) {
    bigint x;
    printf( "Sizeof( Age ) : %d\n", sizeof(bigint) );
    return 0;
}
}