#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4

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

char *del_odd_words(char *s) {
    int len = strlen(s), j = 0, k = 1;
    char *ans = (char*) malloc(sizeof(char) *len);
    for (int i = 0; i < len; i++) {
        while (s[i] == ' ' && i < len && s[i] != '\0')
            i++;
        if (k % 2 == 0) {
            while (s[i] != ' ' && i < len && s[i] != '\0')
                ans[j++] = s[i++];
            ans[j++] = s[i++];
            k++;
        } else {
            while (s[i] != ' ' && s[i] != '\0')
                i++;
            k++;
        }
    }
    ans[j] = '\0';
    free(s);
    return ans;
}

int main () {
    char *s = get_string();
    s = del_odd_words(s);
    printf("Answer: \"%s\"\n", s);
    free(s);
    return 0;
}