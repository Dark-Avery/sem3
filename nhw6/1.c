#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Error with args\n");
        return 0;
    }
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);
    FILE *file = fopen(argv[1], "w");
    if (file == NULL) {
        printf("Error with opening file\n");
        return 1;
    }
    pid_t pid = fork();
    if (pid < 0) {
        printf("Error with fork\n");
        return(1);
    } else if (!pid) {
        char str[80];
        int x;
        scanf("%d", &x);
        getchar();
        fgets(str, 80, stdin);
        while (strcmp(str, "exit\n")) {
            fputs(str, file);
            fflush(file);
            write(fd1[1], &x, sizeof(int));
            write(fd1[1], str, sizeof(str));
            read(fd2[0], &x, 1);
            scanf("%d", &x);
            getchar();
            fgets(str, 80, stdin);
        }
        write(fd1[1], &x, sizeof(int));
        write(fd1[1], str, sizeof(str));
        close(fd1[0]);
        close(fd2[0]);
        exit(0);
    } else {
        char str[80];
        int x, flag = 1;
        read(fd1[0], &x, sizeof(int));
        read(fd1[0], str, sizeof(str));
        while (strcmp(str, "exit\n")) {
            int len = strlen(str);
            if (x >= len)
                for(int i = 0; i < x; i++) {
                    str[i] = '*';
                str[x] = '\n';
                str[x+1] = '\0';
            } else {
                int k = len/2 - 1, s = -1;
                for(int i = 0; i < x; i++) {
                    str[k += i*s] = '*';
                    s = -s;
                }
            }
            fputs(str, file);
            fflush(file);
            write(fd2[1], &flag, sizeof(int));
            read(fd1[0], &x, sizeof(int));
            read(fd1[0], str, sizeof(str));
        }
        wait(NULL);
        fclose(file);
        exit(0);
    }
    return 0;
}