#include <stdio.h>
#include <stdlib.h>
#define N 16

char *get_string() {
    int len = 0, capacity = 0;
    char *s = (char*) malloc(sizeof(char));
    char c, ok;

    ok = scanf("%c", &c);

    while (c != '\n' && ok != -1) {
        s[len++] = c;

        if (len >= capacity * N) {
            capacity += 1;
            s = (char*) realloc(s, N * capacity * sizeof(char));
        }

        ok = scanf("%c", &c);          
    }

    s[len] = '\0';

    return s;
}

int main() {
    char *s = get_string();
    printf("You've wrote: \"%s\"\n", s);
    free(s);
    return 0;
}