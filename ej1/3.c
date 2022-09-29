#include <stdio.h>

int main() {
    int i, j, n;
    long long s;

    scanf("%d%d%d", &i, &j, &n);
    printf("%*c", n, ' ');
    for(int k = i; k < j; k++) {
        printf(" ");
        printf("%*d", n, k);
    }
    printf("\n");
    for(int k = i; k < j; k++) {
        printf("%*d", n, k);
        for(int h = i; h < j; h++) {
            printf(" ");
            s = (long long) k * h;
            printf("%*lld", n, s);
        }
        printf("\n");
    }

    return 0;
}