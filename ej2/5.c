#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

int main(int argc, char** argv) {
    if (argc < 2)
        return 0;
    char *path = argv[1];
    DIR *dir;
    dir = opendir(path);
    struct dirent *dent;
    long long cnt = 0;
    if (!dir)
        return -1;

    while ((dent = readdir(dir)) != NULL) {
        struct stat st;
        char buf[255];
        if (snprintf(buf, sizeof(buf), "%s/%s", path, dent->d_name) < sizeof(buf))
            if (stat(buf, &st) != -1) 
                if (S_ISREG(st.st_mode) && !access(buf, X_OK))
                    if(!(strcmp(".exe", (dent->d_name)+strlen(dent->d_name)-4)))
                        cnt++; 
        
    }
    closedir(dir);
    printf("%lld\n", cnt);
    return 0;
}