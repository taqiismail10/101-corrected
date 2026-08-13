#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cmp_double(const void *a, const void *b) { double x=*(double*)a, y=*(double*)b; return (x>y)-(x<y); }

int main(void) {
    double x[] = {79.919,3.081,0.062,1.961,3.027,6.505,0.021,0.013,6.769,59.89,1.192,34.76,18.38,0.141,43.56,24.42};
    int n = 16;
    double sum=0;
    for(int i=0;i<n;i++) sum+=x[i];
    double mean=sum/n;
    qsort(x,n,sizeof(double),cmp_double);
    printf("i Probability Observed Exponential_Quantile\n");
    for(int i=1;i<=n;i++) {
        double p=(i-0.5)/n;
        double q=-mean*log(1-p);
        printf("%d %.4f %.4f %.4f\n", i,p,x[i-1],q);
    }
    printf("OK: SAMPLE_MEAN %.4f\n", mean);
    printf("OK: COMMENT Use the observed-vs-theoretical pairs for the Q-Q plot; approximate linearity supports exponential distribution.\n");
    return 0;
}
