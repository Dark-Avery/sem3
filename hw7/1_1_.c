#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Error with arguments.\n");
        return 0;
    }
    int output_file = open(argv[argc-1], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (output_file == -1) {
        printf("Error with opening file");
        return 0;
    }
    int *buffer_int = (int*)malloc(sizeof(int));
    while (scanf("%d", buffer_int) != -1) {
        write(output_file, buffer_int, sizeof(int));
    }
    free(buffer_int);
    close(output_file);
    return 0;
}