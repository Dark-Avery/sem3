#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
    struct stat fs;
    long long sum = 0;
    for (int i = 1; i < argc; i++)
        if (lstat(argv[i], &fs) != -1)
            if ((fs.st_size % 1024) == 0)
                if (S_ISREG(fs.st_mode))
                    if (fs.st_nlink == 1) 
                        sum += fs.st_size;
    printf("%lld\n", sum);
    return 0;
}
