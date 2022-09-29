#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_rwx_permissions(const char *str) {
    const char *s = "rwxrwxrwx";
    int len = sizeof(s);
    if (str == NULL)
        return -1;
    if (strlen(str) != len+1)
        return -1;
    int ans = 0;
    for (int i = 0; i < len+1; i++) {
        if (s[i] == str[i])
            ans = ans * 2 + 1;
        else if (str[i] == '-')
            ans *= 2;
        else 
            return -1;
    }
    return ans;
}