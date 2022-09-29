#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

char* ftostr(FILE* in) {
    char* ans = NULL;
    char c;
    int len = 0;
    int ok = fread(&c, sizeof(char), 1, in);
    if (!ok)
        return NULL;
    while (c != '\n' && ok) {
        ans = realloc(ans, ++len);
        ans[len-1] = c;
        ok = fread(&c, sizeof(char), 1, in);
    }
    ans = realloc(ans, len + 1);
    ans[len] = 0;
    return ans;
}

void uniq(int args, char *file, ...) {
    FILE *in = fopen(file, "r");
    if (!in) {
        printf("Error with opening file\n");
        return;
    }
    va_list factor;
    va_start(factor, file);
    char *str;
    int ok = 0;
    int c = 0, d = 0, u = 0, s = 0;
    for (int i = 0; i < args - 1; i++) {
        str = va_arg(factor, char*);
        if (!strcmp(str, "-s")) 
    		ok++; 
    	else if (!strcmp(str, "-c")) {
    		c++; 
            ok = 0;
        } else if (!strcmp(str, "-d")) {
    		d++; 
            ok = 0;
        } else if (!strcmp(str, "-u")) {
    		u++; 
            ok = 0;
        } else if (ok == 1)
    		s = atoi(str);
    }
    if (ok > 1 || c > 1 || d > 1 || u > 1) {
        printf("Error with arguments\n");
        fclose(in);
        return;
    }
    if (u && d) {
        fclose(in);
        return;
    }
    char *str2;
    int count = 1;
    str = ftostr(in);
    while (str) {
        str2 = str;
        if (str = ftostr(in)) {
            if (s >= strlen(str) && s >= strlen(str2))
                ok = 1;
            else if (s > strlen(str) || s > strlen(str2))
                ok = 0;
            else
                ok = !strcmp(str+s, str2+s);
            if (ok) {
                count++;
            } else {
                if ((d && count > 1) || (u && count == 1) || (!d && !u)) {
                    if (c)
                        printf("%7d ", count);
                    printf("%s\n", str2);
                }
                count = 1;
            }
            free(str2);
        } else {
            if ((d && count > 1) || (u && count == 1) || (!d && !u)) {
                if (c)
                    printf("%7d ", count);
                printf("%s\n", str2);
            }
            free(str2);
            break;
        }
    }
    fclose(in);
}

int main(int argc, char** argv) {
    if (argc < 2 || argc > 7) {
        printf("Error with arguments\n");
        return 0;
    }
    if (argc == 2)
        uniq(1, argv[1]); 
    else if (argc == 3)
        uniq(2, argv[2], argv[1]); 
    else if (argc == 4)
        uniq(3, argv[3], argv[1], argv[2]); 
    else if (argc == 5)
        uniq(4, argv[4], argv[1], argv[2], argv[3]); 
    else if (argc == 6)
        uniq(5, argv[5], argv[1], argv[2], argv[3], argv[4]); 
    else
        uniq(6, argv[6], argv[1], argv[2], argv[3], argv[4], argv[5]);
    return 0;
}