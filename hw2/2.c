#include <stdio.h>
#include <stdlib.h>

void matrinp (char **matr, int m, int n) {
    char c;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf ("%c", &c);
            if (c == ' ' || c == '\n' || c == 0) {
                j--;
            } else {
                matr[i][j] = c;
            }
        }
    }
}

void matrout (char **matr, int m, int n) {
    for (int i = 0; i < m; i ++) {
        for (int j = 0; j < n; j++) {
            printf ("%c ", matr[i][j]);
        }
        printf ("\n");
    }
}

void FirstVar (char **matr, int m, int n, char c) {
    char **matr1 = (char **) malloc (sizeof(char*) *m);
    for (int i = 0; i < m; i++) {
        matr1[i] = (char *) malloc (sizeof(char) *n);
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j ++) {
            matr1[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j ++) {
            if (matr1[i][j] != '#') {
                matr1[i][j] = matr[i][j];
                if (matr1[i][j] == c) {
                    for (int t = 0; t < m; t ++) {
                        if (matr[t][j] != c) {
                            matr1[t][j] = '#';
                        }
                    }
                    for (int t = 0; t < n; t ++) {
                        if (matr[i][t] != c) {
                            matr1[i][t] = '#';
                        }
                    }
                    matr1[i][j] = '#';
                }
            }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matr[i][j] = matr1[i][j];
        }
    }
}

void SecondVar (char **matr, int m, int n, char c) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j ++) {
            if (matr[i][j] != '#') {
                if (matr[i][j] == c) {
                    for (int t = 0; t < m; t ++) {
                        if (matr[t][j] != c) {
                            matr[t][j] = '#';
                        }
                    }
                    for (int t = 0; t < n; t ++) {
                        if (matr[i][t] != c) {
                            matr[i][t] = '#';
                        }
                    }
                    matr[i][j] = '#';
                }
            }
        }
    }
}

int main () {
    int m, n;
    char c;
    printf("Enter dims of matrix: ");
    scanf("%d%d", &m, &n);
    char **matr1 = (char **) malloc (sizeof(char*) *m);
    for (int i = 0; i < m; i++) {
        matr1[i] = (char *) malloc (sizeof(char) *n);
    }
    char **matr2 = matr1;
    printf("\nEnter matrix:\n");
    matrinp(matr1, m, n);
    fflush(stdin);
    printf("\nYour matrix:\n");
    matrout(matr1, m, n);
    printf("\nEnter symbol: ");
    scanf("%c", &c);
    printf("\nFirst variant:\n");
    FirstVar(matr1, m, n, c);
    matrout(matr1, m, n);
    printf("\nSecond variant:\n");
    SecondVar(matr2, m, n, c);
    matrout(matr2, m, n);
    return 0;
}