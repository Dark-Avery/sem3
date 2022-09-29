#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void more(FILE *in, int s, int num, int linenum) {
    char c, c1;
    int k, ok;
    int i = 1;
    ok = fread(&c1, 1, 1, in);
    while (ok != 0 && i < linenum) {
        if (c1 == '\n')
            i++;
        ok = fread(&c1, 1, 1, in);
    }
    if (ok == 0)
        return;
    while (c != 'q') {
        c = getchar();
        if (c == '\n') {
            if (ok == 0)
                return;
            i = 0;
            if (s) {
                char ct = c1;
                if (ct == '\n')
                    i++;
                ok = fread(&c1, 1, 1, in);
                while (ok != 0 && i < num) {
                    int f = 1;
                    if (ct != '\n' && c1 == '\n')
                        i++;
                    while (ct == '\n' && c1 == '\n') {
                        ct = c1;
                        ok = fread(&c1, 1, 1, in);
                        f ^= f;
                    }
                    if (f == 0)
                        printf("\n");
                    printf("%c", ct);
                    ct = c1;
                    ok = fread(&c1, 1, 1, in);
                }
            } else {
                while (ok != 0 && i < num) {
                    if (c1 == '\n')
                        i++;
                    printf("%c", c1);
                    ok = fread(&c1, 1, 1, in);
                }
            }
            if (ok == 0)
                return;
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2 || argc > 5) {
        printf("Error with arguments");
        return 0;
    }

    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // сохранение текущего режима
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // изменение

    FILE *in = NULL;
    char c;
    int s = 0, num = 10, linenum = 1;

    for (int i = 1; i < argc; i++) {
        if (i == argc - 1) {
            in = fopen(argv[i], "r");
            if (in == NULL) {
                printf("Error with opening file");
                return 0;
            }
        } else if (strcmp(argv[i], "-s") == 0)
            s = 1;
        else if (strncmp(argv[i], "-", 1) == 0)
            num = atoi(argv[i] + 1);
        else if (strncmp(argv[i], "+", 1) == 0)
            linenum = atoi(argv[i] + 1);
    }
    
    more(in, s, num, linenum);
    printf("\n");

    fclose(in);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // восстановление исходного режима
    return 0;
}