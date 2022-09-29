#include <stdio.h>

void binout (int x) {
    for (int i = sizeof(int) * 8; i > 0; --i) {
        printf("%d", (x & (1 << (i-1))) ? 1 : 0);
    }
    printf("\n");
}

int NoU (int x) {
    int k = 0;
    for (int i = sizeof(int) * 8; i > 0; --i) {
        k += (x & (1 << (i-1))) ? 1 : 0;
    }
    return k;
}

void sort (int *arr, int m) {
    for (int i = 0; i < m - 1 ; i++) {
        for (int j = m - 1; j > i; j--) {
            if (NoU(arr[j - 1]) > NoU(arr[j])) {
                int temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            } else if ((NoU(arr[j - 1]) == NoU(arr[j])) && (arr[j - 1] < arr[j])) {
                int temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main () {
    int m;
    printf("Dim of array: ");
    scanf("%d", &m);
    int arr[m];

    printf("Enter array: \n");
    for (int i = 0; i < m; ++i) {
        scanf("%d", &arr[i]);
    }
    printf("\nYour array: \n");
    for (int i = 0; i < m; ++i) {
        printf("%d = ", arr[i]);
        binout(arr[i]);
    }
    sort(arr, m);
    printf("\nSorted array: \n");
    for (int i = 0; i < m; ++i) {
        printf("%d = ", arr[i]);
        binout(arr[i]);
    }
    return 0;
}