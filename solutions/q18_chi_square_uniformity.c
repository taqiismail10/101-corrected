#include <stdio.h>
#include <math.h>

int main(void) {
    double r[] = {0.34,0.90,0.25,0.89,0.87,0.44,0.12,0.21,0.46,0.67,
                  0.83,0.76,0.79,0.64,0.70,0.81,0.94,0.74,0.22,0.74,
                  0.96,0.99,0.77,0.67,0.56,0.41,0.52,0.73,0.99,0.02,
                  0.47,0.30,0.17,0.82,0.56,0.05,0.45,0.31,0.78,0.05,
                  0.79,0.71,0.23,0.19,0.82,0.93,0.65,0.37,0.39,0.42};
    int n = 50, k = 10, obs[10] = {0};
    for (int i = 0; i < n; i++) {
        int b = (int)(r[i] * k);
        if (b == k) b = k - 1;
        obs[b]++;
    }
    double expected = n / (double)k;
    double chi = 0;
    printf("INTERVAL OBS EXPECTED CONTRIBUTION\n");
    for (int i = 0; i < k; i++) {
        double c = (obs[i] - expected) * (obs[i] - expected) / expected;
        chi += c;
        printf("%.1f-%.1f %d %.2f %.4f\n", i/10.0, (i+1)/10.0, obs[i], expected, c);
    }
    double critical = 16.919; /* df=9, alpha=0.05 */
    printf("OK: CHI_SQUARE %.4f\n", chi);
    printf("OK: CRITICAL_0_05_DF9 %.4f\n", critical);
    printf("OK: DECISION %s\n", chi < critical ? "ACCEPT_UNIFORMITY" : "REJECT_UNIFORMITY");
    return 0;
}
