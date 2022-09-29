#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <limits.h>

#define BLOCK 16

int condition_command(char*** arr_of_command, int start, int end, int backgr);
int conv(char*** arr_of_command, int start, int end, int backgr);
int shell(char*** arr_of_command, int start, int end);
void background(char*** arr_of_command, int start, int end);
char* readstr(void);
char* setspaces(char* str);
char** pars(char* str);
char*** arr_of_arr_string(char** args);
int arrlen(char** arr);
int arrarrlen(char*** arr);
int* redirection(char** command);
char** delete_redirections(char** command);
void stop(int a);
void delete_array(char*** arr);
void cd(char* str);

// void pr(char*** a){
// 	for(int i = 0;i < arrarrlen(a); ++i){
// 		for(int j = 0;j < arrlen(a[i]); j++){
// 			printf("%s;", a[i][j]);
// 		}
// 		printf("\n");
// 	}
// }

// void pr1(char** a){
// 	for(int i = 0;i < arrlen(a); ++i){
// 		printf("%s\n", a[i]);
// 	}
// }

int main(int argc, char** argv) {
	int st;
	char* cwd = (char*)malloc(PATH_MAX);
	while(1) {
		if (getcwd (cwd, PATH_MAX) == NULL)
			printf("getcwd() error\n");
		else
			printf ("\033[1;34m%s\033[1;0m$ ", cwd);
		char* str = readstr();

		if (str == NULL)
			break;
		str = setspaces(str);
        //printf("%s\n", str);
		char** commands = pars(str);
		free(str);
		if (strcmp(commands[0], "exit") == 0)
            break;
		else if (commands[0][0] == 'c' && commands[0][1] == 'd')
			cd(commands[0]+3);
		else {
            // pr1(commands);
			char*** arr = arr_of_arr_string(commands);
            // pr(arr);
			st = shell(arr, 0, arrarrlen(arr));
            
			delete_array(arr);
		}
	}
	free(cwd);
    return 0;
}

char* readstr(){
	char* str = (char*)malloc(BLOCK);
	int n = 0, balans = 0;
	char c;
	c = getchar();
    if (c == EOF) {
		free(str);
		return NULL;
	}
	while (c != '\n') {
		if(n % BLOCK == 0)
			str = (char*)realloc(str, n + BLOCK);
        while (c == '\\') {
            c = getchar();
            if (c == '\n') {
                printf("%c ", 62);
                c = getchar();
            }
        }
        if (c == '(')
            balans--;
        if (c == ')')
            balans++;
        str[n++] = c;
        c = getchar();  
	}
    if (balans > 0) {
        printf("readstr error\n");
        free(str);
        return NULL;
    } 
    while (balans < 0 || c != '\n') {
        if (c == '\n')
            printf("%c ", 62);
        if (n % BLOCK == 0)
            str = (char*)realloc(str, n + BLOCK);
        
        while (c == '\\') {
            c = getchar();
            if (c == '\n') {
                printf("%c ", 62);
                c = getchar();
            }
        }
        if (c == '(')
            balans--;
        if (c == ')')
            balans++;
        if (c != '\n')
            str[n++] = c;
        
        c = getchar();
    }
	if (n % BLOCK == 0)
		str = (char*)realloc(str, n + 1);
	str[n] = '\0';
	return str;
}

char* setspaces(char* str) {
    char c;
    int len = strlen(str), i = 0, k = 0;
    char* anstr = (char*)malloc(len);
    c = str[k++];
    while (c != '\0') {
        if (c == ' ') {
            if (i != 0)
                if (anstr[i-1] != ' ')
                    anstr[i++] = c;
            while (str[k] == ' ' && str[k] != '\0')
                k++;
        } else {
            if (c == '|' || c == ';' || c == '&' || c == '>' || c == '<' || c == '(' || c == ')') {
                if (k != 1 && anstr[i-1] != ' ')
                    anstr[i++] = ' ';
                anstr[i++] = c;
                if (str[k] == c && str[k] != '(' && str[k] != ')') {
                    anstr[i++] = c;
                    k++;
                }
                if (str[k] != '\0')
                    anstr[i++] = ' ';
            } else
                anstr[i++] = c;
        }
        if (i > len - 2)
            anstr = (char*)realloc(anstr, len += BLOCK);
        c = str[k++];
    }
    anstr[i] = '\0';
    free(str);
    return anstr;
}

char** pars(char* str){
	char** ar_arg = (char**)malloc(sizeof(char*) * 4096);
	int j = 0;
	while(1){
		int i = 0;
		while(str[i] != '|' && str[i] != ';' && str[i] != '&' && str[i] != '\0' && str[i] != '(' && str[i] != ')')
			i++;
		if(str[i] == '(') {
			ar_arg[j] = (char*) malloc(sizeof(char) * 2);
			ar_arg[j][0] = str[i];
			ar_arg[j][1] = '\0';
		}
		else if(str[i] != '\0'){
			if(i != 0){
				str[i-1] = '\0';
				int l = strlen(str);
				ar_arg[j] = (char*) malloc(sizeof(char)*(l + 1));
				strcpy(ar_arg[j], str);
				j++;
			}

			if(str[i + 1] != '\0' && str[i + 1] != ' '){
				ar_arg[j] = (char*) malloc(sizeof(char)*3);
				ar_arg[j][0] = str[i];
				ar_arg[j][1] = str[i];
				ar_arg[j][2] = '\0';
				i++;
			}
			else{
				ar_arg[j] = (char*) malloc(sizeof(char)*2);
				ar_arg[j][0] = str[i];
				ar_arg[j][1] = '\0';
			}
		}
		else{
			int l = strlen(str);
			ar_arg[j] = (char*) malloc(sizeof(char)*(l + 1));
			strcpy(ar_arg[j], str);
			ar_arg[j + 1] = NULL;
			break;
		}
		j++;
		if(str[i+1] == '\0'){
			ar_arg[j] = NULL;
			break;
		}
		str += i + 2;
	}
	return ar_arg;
}

void cd(char* str) {
    if (str == NULL)
        printf("No argument\n");
    else
        if (chdir(str) != 0)
            printf("No such directory\n");
    return;
}

char*** arr_of_arr_string(char** args) {
    int len = BLOCK;
    char*** commandArr = (char***)malloc(sizeof(char**) * len);
    int i = 0;
	char* str = args[i];
	while (str != NULL) {
		int s = 0, len1 = BLOCK;
		char** cmdstr = (char**)malloc(sizeof(char*) * len1);
		int k = 0;
		char c = str[k++];
		while(c != '\0') {
			char* newstr = (char*)malloc(sizeof(char) * (strlen(str) + 1));
			int j = 0;
			while (c != '\0' && c != ' '){
				newstr[j++] = c;
				c = str[k++];
			}
			newstr[j] = '\0';
			cmdstr[s++] = newstr;
            if (s % BLOCK == 0)
                cmdstr = realloc(cmdstr, len1 += BLOCK);
			if (c != '\0')
				c = str[k++];
		}
		cmdstr[s] = NULL;
		commandArr[i] = cmdstr;
		free(args[i]);
		i++;
        if (i % BLOCK == 0)
            commandArr = realloc(commandArr, len += BLOCK);
		str = args[i];
	}
	commandArr[i] = NULL;
	free(args);
	return commandArr;
}

int arrlen(char** arr) {
	int i = 0;
	while(arr[i] != NULL)
		i++;
	return i;
}

int arrarrlen(char*** arr) {
	int i = 0;
	while (arr[i] != NULL)
		i++;
	return i;
}

void delete_array(char*** arr) {
	for (int i = 0; i < arrarrlen(arr); i++) {
		for (int j = 0; j < arrlen(arr[i]); j++)
			free(arr[i][j]);
		free(arr[i]);
	}
	free(arr);
}



int shell(char*** arr_of_command, int start, int end) {
	int j = start;
	int status;
	int i;
	for(i = start; i < end; i++) {
		if(strcmp(arr_of_command[i][0], ";") == 0){
			status = condition_command(arr_of_command, j, i, 0);
			j = i + 1;
		} else if(strcmp(arr_of_command[i][0], "&") == 0){
			background(arr_of_command, j, i);
			j = i + 1;
		}
	}
	if(strcmp(arr_of_command[i-1][0], ";") != 0 && strcmp(arr_of_command[i-1][0], "&") != 0)
		status = condition_command(arr_of_command, j, i, 0);
	return status;
}

int* redirection(char** command){
	int* fd = malloc(sizeof(int) * 2);  // 0 - read, 1 - write
	fd[0] = 0;
	fd[1] = 0;
	int i = 0;
	char* redir[3] = {"<", ">", ">>"};
	while(command[i] != NULL){
		if(strcmp(command[i], redir[0]) == 0)
			fd[0] = open(command[i+1], O_RDONLY);
		if(strcmp(command[i], redir[1]) == 0)
			fd[1] = open(command[i+1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if(strcmp(command[i], redir[2]) == 0)
			fd[1] = open(command[i+1], O_WRONLY | O_APPEND | O_CREAT, 0666);
		if(fd[0] == -1 || fd[1] == -1){
			printf("File open error!\n");
			exit(1);
		}
		i++;
	}
	return fd;
}

char** delete_redirections(char** command){
	int i = 0;
	int k = 0;
	char* redir[3] = {"<", ">", ">>"};
	while(command[i] != NULL){
		int flag = 0;
		for(int j = 0; j < 3; j++)
			if(strcmp(command[i], redir[j]) == 0){
				free(command[i]);
				free(command[i+1]);
				flag = 1;
				i += 2;
				break;
			}
		if(command[i] == NULL)
			break;

		if(!flag){
			command[k] = command[i];
			i++;
			k++;
		}
	}
	command[k] = NULL;
	return command;
}



int condition_command(char*** arr_of_command, int start, int end, int backgr){
	int j = start;
	int status;
	for(int i = start; i < end; i++){
		if(strcmp(arr_of_command[i][0], "(") == 0) {
			int cls = 0;
			j++;
			i++;
			while(strcmp(arr_of_command[i][0], ")") != 0 || cls != 0){
                //printf("j = %d  i = %d com = %s \n", j, i, arr_of_command[i][0]);
				if(strcmp(arr_of_command[i][0], "\0") == 0){
					// printf("breaket error!\n");
					exit(0);
				}
				if(strcmp(arr_of_command[i][0], ")") == 0)
					cls--;
				if(strcmp(arr_of_command[i][0], "(") == 0)
					cls++;
				i++;
			}
            //printf("j = %d  i = %d com = %s \n", j, i, arr_of_command[i][0]);
			status = shell(arr_of_command, j, i);
			j = i + 1;

		}
		else if(strcmp(arr_of_command[i][0], "&&") == 0 || strcmp(arr_of_command[i][0], "||") == 0){
			if(j != i)
				status = conv(arr_of_command, j, i, backgr);
			if((status != 0 && strcmp(arr_of_command[i][0], "&&") == 0)){
				while(++i < end)
					if(strcmp(arr_of_command[i][0], "||") == 0)
						break;
			}
			else if(status == 0 && strcmp(arr_of_command[i][0], "||") == 0)
				while(++i < end)
					if(strcmp(arr_of_command[i][0], "&&") == 0)
						break;

			j = i + 1;
		}
	}
	if(j < end){
		int ls = conv(arr_of_command, j, end, backgr);
		return ls | status;
	}
	return status;
}

void stop(int a){
    pid_t pid = getpid();
    printf("Stopped pid = %d", pid);
    signal(SIGINT,SIG_DFL);
    signal(SIGTSTP,SIG_DFL);
}

int conv(char*** arr_of_command, int start, int end, int backgr){

	pid_t pid;
	int fd[2];
	int *redir;

	redir = redirection(arr_of_command[start]);
	arr_of_command[start] = delete_redirections(arr_of_command[start]);
	int oldfd0;

    for(int i = start; i < end; i++){
    	if(strcmp(arr_of_command[i][0], "|") != 0 && strcmp(arr_of_command[i][0], "(") != 0 && strcmp(arr_of_command[i][0], ")") != 0){

	        if (pipe(fd) < 0){
	    		printf("pipe error!\n");
	    		exit(1);
			}
	        if((pid = fork()) < 0) {
	        	printf("Fork error!\n");
	        	exit(1);
	        }
	        if(!pid){
	            if(!backgr){
	            	signal(SIGINT,stop); 
	            	signal(SIGTSTP,stop);
	            }

	            if (i != end - 1)
	                dup2(fd[1], 1);
	            else if (redir[1] != 0){
	                dup2(redir[1], 1);
	                close(redir[1]);
	            }
				
	            if (i != start){
	                dup2(oldfd0, 0);
	                close(oldfd0);
	            }
	            else if (redir[0] != 0){
	                dup2(redir[0], 0);
	                close(redir[0]);
	            }
	            close(fd[1]);
	            close(fd[0]);
	            if(execvp(arr_of_command[i][0], arr_of_command[i]) == -1);
	            	printf("execvp error!\n");
                    printf("%s\n", arr_of_command[i][0]);
	            exit(0);

	        }
	        close(fd[1]);
	        oldfd0 = fd[0];
        }
    }
    free(redir);
    int lstatus = 0;
    waitpid(pid, &lstatus, 0);
    while (wait(NULL) != -1);

    if(WIFEXITED(lstatus) != 0)
		return WEXITSTATUS(lstatus);
	return 1;
}

void background(char*** arr_of_command, int start, int end){
	pid_t pid;
	if((pid = fork()) < 0) {
    	printf("Fork error!\n");
    	exit(1);
    }
    if(!pid){
    	pid_t pid1;
    	if((pid1 = fork()) < 0) {
	        printf("Fork error!\n");
	       	exit(1);
	  	}
	    if(!pid1){
	    	signal(SIGINT, SIG_IGN);
	    	int file1 = open("/dev/null", O_RDONLY);
	    	int file2 = open("/dev/null", O_WRONLY);
	    	dup2(file2, 1);
       		dup2(file1, 0);
	    	condition_command(arr_of_command, start, end, 1);
	    	exit(0);
	    }
	    exit(0);
    }
	wait(NULL);
}