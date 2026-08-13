#include <stdio.h>
#include <math.h>

void analyze(const char *name, double x[], int n) {
    double mu0 = 4.3, epsilon = 1.0, tcrit = 2.776;
    double sum = 0;
    for (int i=0;i<n;i++) sum += x[i];
    double mean = sum/n;
    double ss = 0;
    for (int i=0;i<n;i++) ss += (x[i]-mean)*(x[i]-mean);
    double sd = sqrt(ss/(n-1));
    double se = sd/sqrt(n);
    double half = tcrit*se;
    double low = mean-half, high = mean+half;
    double tstat = fabs(mean-mu0)/se;
    printf("MODEL: %s\n", name);
    printf("OK: MEAN %.4f SD %.4f SE %.4f\n", mean, sd, se);
    printf("OK: CI_95 %.4f %.4f\n", low, high);
    printf("OK: T_STAT %.4f T_CRITICAL %.4f\n", tstat, tcrit);
    printf("OK: CONTAINS_OBSERVED_MEAN %s\n", (low <= mu0 && mu0 <= high) ? "YES" : "NO");
    printf("OK: MEAN_WITHIN_ERROR_MARGIN %s\n\n", fabs(mean-mu0) <= epsilon ? "YES" : "NO");
}

int main(void) {
    double first[] = {2.79,5.12,2.24,3.13,4.38};
    double revised[] = {5.37,4.98,5.29,6.74,2.49};
    analyze("FIRST_MODEL", first, 5);
    analyze("REVISED_MODEL", revised, 5);
    return 0;
}
