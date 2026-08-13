#include <stdio.h>
#include <math.h>

void analyze(const char *label, double x[], int n) {
    double tcrit = 3.18;
    double sum=0;
    for(int i=0;i<n;i++) sum += x[i];
    double mean=sum/n;
    double ss=0;
    for(int i=0;i<n;i++) ss += (x[i]-mean)*(x[i]-mean);
    double sd=sqrt(ss/(n-1));
    double se=sd/sqrt(n);
    double ci_half=tcrit*se;
    double pi_half=tcrit*sd*sqrt(1.0+1.0/n);
    printf("MEASURE: %s\n", label);
    printf("OK: DEGREE_OF_FREEDOM %d\n", n-1);
    printf("OK: MEAN %.4f SD %.4f STANDARD_ERROR %.4f\n", mean, sd, se);
    printf("OK: CONFIDENCE_INTERVAL_95 %.4f %.4f\n", mean-ci_half, mean+ci_half);
    printf("OK: PREDICTION_INTERVAL_95 %.4f %.4f\n\n", mean-pi_half, mean+pi_half);
}

int main(void) {
    double util[] = {0.808,0.875,0.708,0.842};
    double sys[]  = {3.74,4.53,3.84,3.98};
    analyze("ABLE_UTILIZATION", util, 4);
    analyze("ABLE_AVERAGE_SYSTEM_TIME", sys, 4);
    return 0;
}
