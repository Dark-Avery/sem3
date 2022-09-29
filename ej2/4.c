#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv){
	if (argc < 2)
		return 0;

	int file;
	if ((file = open(argv[1], O_RDONLY)) == -1)
		return 1;
	
	unsigned short x, buf;
	int count = read(file, &buf, 2);
    x = (buf << 8) | (buf >> 8);
	while (x % 2 == 1 && count > 0) {
		count = read(file, &buf, 2);
        x = (buf << 8) | (buf >> 8);
    }
	if (count <= 0)
		return 0;

	unsigned short min = x;
	while ((count = read(file, &buf, 2)) != 0) {
        x = (buf << 8) | (buf >> 8);
		if (x % 2 == 0 && x < min)
			min = x;
    }

	close(file);
	printf("%hu\n", min);
	return 0;
}