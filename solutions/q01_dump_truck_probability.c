#include <stdio.h>

int main(void) {
    int travel[] = {110, 130, 170, 180};
    int low[]    = {  1,  36,  76,  91};
    int high[]   = { 35,  75,  90, 100}; /* 00 is treated as 100 */
    int n = 4;
    double cumulative = 0.0;

    printf("TRAVEL_TIME PROBABILITY CUMULATIVE_PROBABILITY RANDOM_NUMBER\n");
    for (int i = 0; i < n; i++) {
        int count = high[i] - low[i] + 1;
        double p = count / 100.0;
        cumulative += p;
        printf("%d %.2f %.2f %02d-%02d\n", travel[i], p, cumulative,
               low[i] == 100 ? 0 : low[i], high[i] == 100 ? 0 : high[i]);
    }
    printf("OK: TOTAL_PROBABILITY %.2f\n", cumulative);
    return 0;
}
