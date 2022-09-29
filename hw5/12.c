#include <stdio.h>
#include <stdlib.h>
#define BINPRINT(x) do {         \
    long long y = 0;                \
    printf("X = ");                 \
    int i = sizeof(x)*8;            \
    for(int j = i; j != 0; j--) {   \
        if (x & 1 == 1)   {           \
            y = (y << 1);           \
            y++;                    \
        }                           \
        else                        \
            y = (y << 1);           \
        x = x >> 1;                 \
    }                               \
    for(i; i != 0; i--) {           \
        if (y&1 == 1)               \
            printf("1");            \
        else                        \
            printf("0");            \
        y = y >> 1;                 \
    }                               \
    printf("\n");                   \
} while(0)

int main()
{
    char c = -3;
    if (c) 
        BINPRINT(c); 
    else 
        printf("Zero!\n");
    BINPRINT((short)7);
    long x = 15;
    if(x) 
        BINPRINT(x); 
    else 
        printf("Zero!\n");
    BINPRINT((long long)x);
    return 0;
}
