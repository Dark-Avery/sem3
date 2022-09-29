#include <stdio.h>

int main() {
    int ok;
    char c;
    unsigned long long s;

    ok = scanf("%c", &c);
    while (ok != -1) {
        if (c >= '0' && c <= '9')
            s += (unsigned long long)(c - '0');
        else if (c >= 'a' && c <= 'f')
            s += (unsigned long long)((c - 'a')+10);
        else if (c >= 'A' && c <= 'F')
            s += (unsigned long long)((c - 'A')+10);
        ok = scanf("%c", &c);
    }
    printf("%llu", s);
    return 0;
}