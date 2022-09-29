#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2)
        return 0;
    struct node {
        FILE *file;
        long long elem;
        int status;
    } files[argc-1];
    for (int i = 0; i < argc-1; i++) {
        files[i].file = fopen(argv[i+1], "r");
        if (files[i].file == NULL)
            files[i].status = -1;
        else 
            files[i].status = fscanf(files[i].file, "%lld", &files[i].elem);
    }

    int s = 0;
    for (int i = 0; i < argc-1; i++)
        if (files[i].status != -1)
            s++;

    while (s) {
        long long min = 0;
        int index_min = 0;
        for (int i = 0; i < argc-1; i++)
            if (files[i].status != -1) {
                min = files[i].elem;
                index_min = i;
                break;
            }
        for (int i = index_min+1; i < argc-1; i++)
            if (files[i].status != -1)
                if (files[i].elem < min) {
                    min = files[i].elem;
                    index_min = i;
                }
        if (files[index_min].status != -1)
            printf("%lld\n", min);
        if ((files[index_min].status = fscanf(files[index_min].file, "%lld", &files[index_min].elem)) == -1)
            s--;
    }

    for (int i = 0; i < argc-1; i++)
        if (files[i].file != NULL)
            fclose(files[i].file);
    return 0;
}