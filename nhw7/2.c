#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

pid_t pid;
int fd;

int son() {
    char c;
    int ok;
    while(ok = read(fd, &c, 1)) {
        if (c != ' ' && c != '\n')
            break;
    }
    if (ok)
        printf("Son ");
    while(ok) {
        if (c == ' ' || c == '\n')
            break;
        printf("%c", c);
        ok = read(fd, &c, 1);
    }
    printf("\n");
    if (ok == 0) {
        kill(pid, SIGINT);
        kill(getppid(), SIGINT);
    } else
        kill(getppid(), SIGUSR1);
    return 0;
}

int father() {
    char c;
    int ok;
    while(ok = read(fd, &c, 1)) {
        if (c != ' ' && c != '\n')
            break;
    }
    if (ok)
        printf("Father ");
    while(ok) {
        if (c == ' ' || c == '\n')
            break;
        printf("%c", c);
        ok = read(fd, &c, 1);
    }
    printf("\n");
    if (ok == 0) {
        kill(pid, SIGINT);
        kill(getppid(), SIGINT);
    } else
        kill(pid, SIGUSR1);
    return 0;
}

int al() {
    kill(pid, SIGINT);
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2)
        return 0;
    fd = open(argv[1], O_RDONLY);
    pid = fork();
    if (pid < 0) {
        printf("Error with fork\n");
        return -1;
    } else if (!pid) {
        signal(SIGUSR1, son);
        kill(getppid(), SIGUSR1);
        for(;;);
    } else {
        alarm(1);
        signal(SIGUSR1, father);
        signal(SIGALRM, al);
        wait(NULL);
        exit(0);
    }
    return 0;
}