#include <stdio.h>
#include <stdlib.h>
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

char *del_odd_words(char *s, char *s2) {
    int len = strlen(s), len2 = strlen(s2), j = 0, k = 1, l = 0, i = 0;
    char *ans = (char*) malloc(strlen(s)+strlen(s2));
    while (j < len+len2) {
        while (s[i] == ' ' && i < len && s[i] != '\0')
            i++;
        while (s2[l] == ' ' && l < len2 && s2[l] != '\0')
            l++;
        if (k % 2 != 0) {
            while (s[i] != ' ' && s[i] != '\0')
                ans[j++] = s[i++];
            ans[j++] = s[i++];
            k++;   
        } else {
            while (s2[l] != ' ' && s2[l] != '\0')
                ans[j++] = s2[l++];
            ans[j++] = s2[l++];
            k++;
        }
    }
    ans[j] = '\0';
    return ans;
}

int main () {
    char *s = get_string();
    char *s2 = get_string();
    s = del_odd_words(s, s2);
    printf("Answer: \"%s\"\n", s);
    return 0;
}






