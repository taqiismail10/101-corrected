#include <stdio.h>
#include <math.h>

int main(void) {
    double r[] = {0.2357, 0.4146, 0.3353, 0.9952};
    int n = 4;
    printf("CAR RANDOM_NUMBER INTERARRIVAL_TIME\n");
    for (int i = 0; i < n; i++) {
        double x = 3.0 * sqrt(r[i]); /* F(x)=x^2/9, so x=sqrt(9R)=3sqrt(R) */
        printf("%d %.4f %.4f\n", i+1, r[i], x);
    }
    printf("OK: INVERSE_FORMULA x = 3*sqrt(R)\n");
    return 0;
}
