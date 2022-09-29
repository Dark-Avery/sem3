#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (argc < 3)
        return 0;
	int file = open("fres.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	for (int i = 2; i < argc; i++){
		dprintf(file, "===%s===\n", argv[i]);
		int fd[2];
		pipe(fd);
		pid_t pid1 = fork();
		if (!pid1) {
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			execlp("ls", "ls", "-l", argv[i], NULL);
			_exit(1);
		}
		close(fd[1]);
		pid_t pid2 = fork();
		if (!pid2) {
			dup2(fd[0], 0);
			dup2(file, 1);
			close(fd[0]);
			execlp("grep", "grep", argv[1], NULL);
			_exit(1);
		}
		close(fd[0]);
		wait(NULL);
		wait(NULL);
	}
	close(file);
	return 0;
}
