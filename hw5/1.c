#include <stdio.h>
#define BINPRINT(x) \
    do { \
        for (int i = 0; i < sizeof(x) * 8; i++) { \
            printf("%d", 1 & (x >> (sizeof(x) * 8 - i - 1)) ? 1 : 0); \
        } \
        printf("\n"); \
    } while (0)

int main() {
    char c = -3;
    if (c)
        BINPRINT(c); 
    else 
        printf("Zero!\n");
    BINPRINT((short)7);
    long x = 15;
    if (x) 
        BINPRINT(x); 
    else 
        printf("Zero!\n");
    BINPRINT((long long)x);
    return 0;
}