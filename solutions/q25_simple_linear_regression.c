#include <stdio.h>

int main(void) {
    double x[] = {100,100,100,150,150,150,200,200,200,250,250,250,300,300,300};
    double y[] = {8.3,7.9,7.4,9.6,8.5,9.2,10.9,13.5,11.3,12.7,14.6,15.7,16.5,17.5,18.3};
    int n = 15;
    double sx=0, sy=0;
    for(int i=0;i<n;i++){ sx+=x[i]; sy+=y[i]; }
    double xb=sx/n, yb=sy/n;
    double sxx=0, sxy=0;
    for(int i=0;i<n;i++){ sxx+=(x[i]-xb)*(x[i]-xb); sxy+=(x[i]-xb)*(y[i]-yb); }
    double beta1=sxy/sxx;
    double beta0=yb-beta1*xb;
    printf("OK: BETA0 %.6f\n", beta0);
    printf("OK: BETA1 %.6f\n", beta1);
    printf("OK: REGRESSION_EQUATION Y = %.6f + %.6f*x\n", beta0, beta1);
    printf("CLAIMS PREDICTED_HOURS\n");
    for(int claims=400; claims<=1000; claims+=100) {
        printf("%d %.2f\n", claims, beta0 + beta1*claims);
    }
    return 0;
}
