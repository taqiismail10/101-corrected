#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cmp_double(const void *a, const void *b) { double x=*(double*)a, y=*(double*)b; return (x>y)-(x<y); }

int main(void) {
    double x[] = {99.79,99.56,100.17,100.33,100.26,100.31,99.98,99.83,101.23,100.27,100.02,100.47,99.55,99.62,99.65,99.82};
    int n = 16;
    double sum = 0;
    for (int i=0;i<n;i++) sum += x[i];
    double mean = sum/n;
    qsort(x,n,sizeof(double),cmp_double);
    printf("i Probability Observed Sorted_Observed Exponential_Quantile\n");
    for (int i=1;i<=n;i++) {
        double p=(i-0.5)/n;
        double q=-mean*log(1-p);
        printf("%d %.4f %.4f %.4f\n", i,p,x[i-1],q);
    }
    printf("OK: SAMPLE_MEAN %.4f\n", mean);
    printf("OK: COMMENT If points are close to a straight line, exponential assumption is acceptable; here values cluster near 100, so exponential fit is weak.\n");
    return 0;
}
