#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
    int i = 0, k = 0, ok, max;
    if (argc < 2) {
        printf("No arguments");
        return 0;
    }
    max = atoi(argv[2]);
    FILE *in = fopen(argv[1],"r"), *out = fopen(argv[1],"r+"), *temp = tmpfile();
    if (in == NULL || out == NULL) {
        printf("Error with opening file");
        return 0;
    }
    char c;
    ok = fread(&c, sizeof(char), 1, in);
    while (ok != 0) {
        if (c != '\n') {
            fwrite(&c, sizeof(char), 1, temp);
            i++;
        } else {
            rewind(temp);
            if (i <= max) {
                for (int j = 0; j < i; j++) {
                    fread(&c, sizeof(char), 1, temp);
                    fwrite(&c, sizeof(char), 1, out);
                    k++;
                }
                rewind(temp);
                fputc('\n', out);
            }
            i = 0;
        }
        ok = fread(&c, sizeof(char), 1, in);
    }
    fclose(temp);
    fclose(in);
    ftruncate(fileno(out), k);
    fclose(out);
    return 0;
}