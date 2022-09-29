#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--)
    {
		c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


char* my_or_not_itoa(int n, int* len_of_string)
{
    char* outputting_string = (char*)malloc(sizeof(char));
    int sign_n = 0;
    int i;
    char flag = 0;
    if (n == 0x80000000) { n += 1; flag = 1; } // in task - 32 bits for a number
    if (n < 0) { sign_n = -1; n = -n; }
    i = 0;
	do
	{
	    outputting_string[i] = n % 10 + '0';
	    i++;
	    outputting_string = realloc(outputting_string, i + 1);
	} while ((n /= 10) != 0);
	if (sign_n) { outputting_string[i] = '-'; i++; outputting_string = realloc(outputting_string, i + 1); }
	outputting_string[i] = 0;
	reverse(outputting_string);
	if (flag) { outputting_string[i-1] += 1; }
	*len_of_string = i;
	return outputting_string;
}


int main(int argc, char** argv)
{
	if (argc < 3) { puts("To few arguments! Must be exactly 3"); return 0; }
    struct stat stats_of_FIRST_input_file;
	struct stat stats_of_SECOND_input_file;
	int descriptor_of_a_FIRST_file = open(argv[1], O_RDWR, 0666);
	int descriptor_of_a_SECOND_file = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
	stat(argv[1], &stats_of_FIRST_input_file);
	stat(argv[2], &stats_of_SECOND_input_file);
	if (stats_of_FIRST_input_file.st_ino == stats_of_SECOND_input_file.st_ino)
	{
	    puts("ERORR!!! Names pointing on a one file");
	    close(descriptor_of_a_FIRST_file);
		close(descriptor_of_a_SECOND_file);
		return 0;
	}
	if (descriptor_of_a_FIRST_file == -1) { printf("Failed to open "); puts(argv[1]); return 0; }
	if (descriptor_of_a_SECOND_file == -1) { printf("Failed to open "); puts(argv[2]); return 0; }
	if (!stats_of_FIRST_input_file.st_size) { printf("Empty file - "); puts(argv[1]); return 0; }
	int len_of_string;
	int* buffer_for_integers = (int*)malloc(sizeof(int));
	char* string_number;
	while (read(descriptor_of_a_FIRST_file, buffer_for_integers, sizeof(int))) /* write only negative first*/
	{
		if (*buffer_for_integers < 0)
		{
			write(descriptor_of_a_SECOND_file, buffer_for_integers, sizeof(int));
		}
	}
	
	lseek(descriptor_of_a_FIRST_file, 0, SEEK_SET);
	
	while (read(descriptor_of_a_FIRST_file, buffer_for_integers, sizeof(int)))/* in second only negative, so write zero and positive */
	{
		if (*buffer_for_integers >= 0)
		{
			write(descriptor_of_a_SECOND_file, buffer_for_integers, sizeof(int));
		}
	}
	
	lseek(descriptor_of_a_FIRST_file, 0, SEEK_SET);// set on start of both files
	lseek(descriptor_of_a_SECOND_file, 0, SEEK_SET);
	
	// in second are all sorted numbers allocated
	while (read(descriptor_of_a_SECOND_file, buffer_for_integers, sizeof(int)))// copy from a second to a first one, as task wanted
	{
		write(descriptor_of_a_FIRST_file, buffer_for_integers, sizeof(int));
	}
	
	lseek(descriptor_of_a_FIRST_file, 0, SEEK_SET);
	remove(argv[2]);// second file is binary now, dont need it as binary anymore, so destroy
	descriptor_of_a_SECOND_file = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);// create again but for text
		
	while (read(descriptor_of_a_FIRST_file, buffer_for_integers, sizeof(int)))
	{
		len_of_string = 0;
		string_number = my_or_not_itoa(*buffer_for_integers, &len_of_string);
		write(descriptor_of_a_SECOND_file, string_number, len_of_string);
		write(descriptor_of_a_SECOND_file, "\n", 1);
		free(string_number);
	}
	
	free(buffer_for_integers);
	close(descriptor_of_a_FIRST_file);
	close(descriptor_of_a_SECOND_file);
	return 0;
}
