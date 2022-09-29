#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Error with arguments\n");
        return 0;
    }

    FILE *in = NULL, *out = NULL;
    char c;

    in = fopen(argv[argc - 2], "r");
    out = fopen(argv[argc - 1], "w");
    if (in == NULL || out == NULL) {
        printf("Error with open files\n");
        return 0;
    }
    
    struct rf {
        int count;
        long int beg;
    };

    struct rf *readfile = (struct rf*)malloc(sizeof(struct rf));
    readfile[0].count = 0;

    rewind(in);
    int k = 0, f = 1, j = 0;
    while(fread(&c, 1, 1, in)) {
        if (f) {
            f = 0;
            readfile[k].beg = j;
        }
        if (c != '\n') 
            readfile[k].count++;
        else {
            f = 1;
            k++;
            readfile = (struct rf*)realloc(readfile, sizeof(struct rf)*(k+1));
            readfile[k].count = 0;
        }
        j++;
    }
    scanf("%d", &j);
    while (j != 0) {
        if (j > 0 && j <= k) {
            fseek(in, readfile[j-1].beg, SEEK_SET);
            for (int i = 0; i < readfile[j-1].count; i++) {
                fread(&c, 1, 1, in);
                printf("%c", c);
            }
        }
        printf("\n");
        scanf("%d", &j);
    }
    for (int i = 0; i < k - 1; i++)
        for(int j = 0; j < k - i - 1; j++)
            if(readfile[j].count > readfile[j+1].count) { 
                struct rf tmp = readfile[j]; 
                readfile[j] = readfile[j+1] ; 
                readfile[j+1] = tmp; 
            } 
    for (int j = 0; j < k; j++) {
        fseek(in, readfile[j].beg, SEEK_SET);
        for (int i = 0; i < readfile[j].count; i++) {
            fread(&c, 1, 1, in);
            fwrite(&c, 1, 1, out);
        }
        fputc('\n', out);
    }

    free(readfile);
    fclose(in);
    fclose(out);
    return 0;
}