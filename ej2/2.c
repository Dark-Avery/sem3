#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc < 2)
        return 0;
    char str[10] = "rwxrwxrwx";
    int x;
    for(int i = 1; i < argc; i++) {
        x = atoi(argv[i]);
        char s[10];
        for(int j = 0; j < 10; j++)
            s[j] = str[j];
        int buf = x%10;
        x /= 10;
        for(int j = 8; j > 5; j --) {
            if (!(buf&1)) {
                s[j] = '-';
            }
            buf >>= 1;
        }
        buf = x%10;
        x /= 10;
        for(int j = 5; j > 2; j --) {
            if (!(buf&1))
                s[j] = '-';
            buf >>= 1;
        }
        for(int j = 2; j >= 0; j --) {
            if (!(x&1))
                s[j] = '-';
            x >>= 1;
        }
        printf("%s\n", s);
    }
    return 0;
}
