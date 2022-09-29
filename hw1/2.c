#include <stdio.h>

void binout(int x) {
    for (int i = sizeof(int) * 8; i > 0; --i) {
        printf("%d", (x & (1 << (i-1))) ? 1 : 0);
    }
    printf("\n");
}

unsigned cyclsh(unsigned x, unsigned n, int k) {
    unsigned i;
    if (k) {        //right
        while (n) {
            i = x & 1;
            x >>= 1;
            if (i)
                x |= (1 << (sizeof(unsigned)*8 - 1));
            --n;
        }
    } else {        //left
        while (n) {
            i = x & (1 << (sizeof(unsigned)*8 - 1));
            x <<= 1;
            if (i)
                x |= 1;
            --n;
        }
    }
    return x;
}

int main () {
    int x, k;
    unsigned n, x1;

    printf("Enter signed int: ");
    scanf("%d", &x);
    printf("Binary:\n");
    binout(x);
    printf("\n");

    printf("Enter unsigned int: ");
    scanf("%u", &x1);
    printf("Binary:\n");
    binout(x1);
    printf("Enter number of shifts: ");
    scanf("%u", &n);
    printf("Enter direction(0 for left, 1 for right): ");
    scanf("%d", &k);
    printf("Shifted binary:\n");
    binout(cyclsh(x1, n, k));
    printf("\n");

    return 0;
}