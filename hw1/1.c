#include <stdio.h>

int main () {
    double x, x1, e, x0;
    printf("epsilon = ");
    scanf("%lf", &e);
    while (scanf("%lf", &x) != -1) {
        x0 = 1;
        x1 = (1 + x)/2;
        while (((x1 - x0) >= e) || ((x0 - x1) >= e)) {
            x0 = x1;
            x1 = (x0 + x/x0)/2;
        }
        printf("sqrt(%lf) = %lf\\%f\\%g\\%.10g\\%e\n", x, x1, x1, x1, x1, x1);
    }
    
    return 0;
}