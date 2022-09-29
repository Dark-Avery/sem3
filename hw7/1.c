#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void reverse(char *s) {
    int c, i, j;
    for(i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
    return;
}

void itoa(int n, char *s) {
    int i, sign;
    if (n == -2147483648) {
        strcpy(s, "-2147483648\0");
        return;
    }
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while (n /= 10);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    return;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Error with arguments.\n");
        return 0;
    }
    int input_file = open(argv[argc-2], O_RDWR, 0666);
    int output_file = open(argv[argc-1], O_RDWR | O_CREAT | O_TRUNC, 0666);
    struct stat stat_file1;
    struct stat stat_file2;
    stat(argv[argc-2], &stat_file1);
	stat(argv[argc-1], &stat_file2);
    if (stat_file1.st_ino == stat_file2.st_ino) {
        printf("Error. The names point to a single file.\n");
        close(input_file);
        close(output_file);
        return 0;
    }
    if (input_file == -1 || output_file == -1) {
        printf("Error with opening files");
        return 0;
    }

    int *buffer_int = (int*)malloc(sizeof(int));
    while (read(input_file, buffer_int, sizeof(int))) {
		if (*buffer_int < 0) {
			write(output_file, buffer_int, sizeof(int));
		}
	}
    lseek(input_file, 0, SEEK_SET);
    while (read(input_file, buffer_int, sizeof(int))) {
		if (*buffer_int >= 0) {
			write(output_file, buffer_int, sizeof(int));
		}
	}

    lseek(input_file, 0, SEEK_SET);
    lseek(output_file, 0, SEEK_SET);
    while (read(output_file, buffer_int, sizeof(int))) {
		write(input_file, buffer_int, sizeof(int));
	}

    lseek(input_file, 0, SEEK_SET);
    remove(argv[argc-1]);
    output_file = open(argv[argc-1], O_RDWR | O_CREAT | O_TRUNC, 0666);

    while (read(input_file, buffer_int, sizeof(int))) {
        char *buffer_char = (char*)malloc(sizeof(char)*12);
        itoa(*buffer_int, buffer_char);
        write(output_file, buffer_char, strlen(buffer_char));
        write(output_file, " ", 1);
        free(buffer_char);
	}
    free(buffer_int);
    close(input_file);
    close(output_file);
    return 0;
}