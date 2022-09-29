// Задача.
// Написать программу, которая
// 1) создает исполняемый файл, выводящий на экран «Hello, world» ,  т.е. готовит код и компилирует,
// 2) запускает его на выполнение.
//#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    FILE *f = fopen("1_1.c", "w");
    fprintf(f, "#include <stdio.h>\nint main() {    printf(\"Hello, world\\n\");    return 0;}");
    fclose(f);
    pid_t proc;
    proc = fork();
    if (proc < 0)
        return -1;
    if (proc == 0) {
        execlp("gcc", "gcc", "1_1.c", "-o", "1_1", NULL);
        exit(-1);
    }
    wait(NULL);
    proc = fork();
    if (proc < 0)
        return -1;
    if (proc == 0) {
        execlp("./1_1", "1_1", NULL);
        exit(-1);
    }
    wait(NULL);
    return 0;
}