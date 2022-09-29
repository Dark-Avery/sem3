#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

pid_t pid;

int son() {
    printf("Son\n");
    kill(getppid(), SIGUSR1);
    return 0;
}

int father() {
    printf("Father\n");
    kill(pid, SIGUSR1);
    return 0;
}

int al() {
    kill(pid, SIGINT);
    return 0;
}

int main() {
    pid = fork();
    if (pid < 0) {
        printf("Error with fork\n");
        return -1;
    } else if (!pid) {
        signal(SIGUSR1, son);
        kill(getppid(), SIGUSR1);
        for(;;);
    } else {
        alarm(3);
        signal(SIGALRM, al);
        signal(SIGUSR1, father);
        wait(NULL);
        for(;;) {
            sleep(1);
            printf("Father\n");
        }
    }
    return 0;
}