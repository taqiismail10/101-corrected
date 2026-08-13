#include <stdio.h>
#include <math.h>

void analyze(const char *pair, double d[], int n) {
    double tcrit = 2.262;
    double sum=0;
    for(int i=0;i<n;i++) sum+=d[i];
    double mean=sum/n;
    double ss=0;
    for(int i=0;i<n;i++) ss+=(d[i]-mean)*(d[i]-mean);
    double sd=sqrt(ss/(n-1));
    double se=sd/sqrt(n);
    double half=tcrit*se;
    printf("PAIR: %s\n", pair);
    printf("OK: POINT_ESTIMATOR %.4f\n", mean);
    printf("OK: STANDARD_ERROR %.4f\n", se);
    printf("OK: CI_95 %.4f %.4f\n\n", mean-half, mean+half);
}

int main(void) {
    double d12[] = {0.66,0.46,-0.04,-0.77,-0.50,-0.99,0.71,0.44,1.62,6.41};
    double d13[] = {5.98,2.59,3.76,1.23,2.48,5.40,2.71,6.12,6.66,19.93};
    double d14[] = {1.09,0.68,0.41,-0.41,-0.36,-0.21,0.80,1.15,1.83,7.60};
    analyze("MODEL_1_MINUS_MODEL_2", d12, 10);
    analyze("MODEL_1_MINUS_MODEL_3", d13, 10);
    analyze("MODEL_1_MINUS_MODEL_4", d14, 10);
    printf("OK: BEST_MODEL MODEL_3\n");
    printf("OK: REASON Model 3 has the largest positive reduction in response time versus Model 1.\n");
    return 0;
}
