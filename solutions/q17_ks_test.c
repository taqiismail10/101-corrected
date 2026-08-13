#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cmp_double(const void *a, const void *b) {
    double x = *(double*)a, y = *(double*)b;
    return (x > y) - (x < y);
}

int main(void) {
    double x[] = {0.41, 0.86, 0.17, 0.05, 0.93, 0.34};
    int n = 6;
    double dplus = 0, dminus = 0;
    qsort(x, n, sizeof(double), cmp_double);
    printf("i Ri i/n D_PLUS (i-1)/n D_MINUS\n");
    for (int i = 1; i <= n; i++) {
        double dp = i/(double)n - x[i-1];
        double dm = x[i-1] - (i-1)/(double)n;
        if (dp > dplus) dplus = dp;
        if (dm > dminus) dminus = dm;
        printf("%d %.2f %.4f %.4f %.4f %.4f\n", i, x[i-1], i/(double)n, dp, (i-1)/(double)n, dm);
    }
    double D = dplus > dminus ? dplus : dminus;
    double critical = 0.669; /* K-S critical value for n=6, alpha=0.01 */
    printf("OK: D_PLUS %.4f\n", dplus);
    printf("OK: D_MINUS %.4f\n", dminus);
    printf("OK: D %.4f\n", D);
    printf("OK: CRITICAL_0_01 %.4f\n", critical);
    printf("OK: DECISION %s\n", D < critical ? "ACCEPT_UNIFORMITY" : "REJECT_UNIFORMITY");
    return 0;
}
