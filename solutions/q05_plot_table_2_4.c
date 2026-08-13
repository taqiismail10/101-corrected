#include <stdio.h>
#include <stdlib.h>

int cmp_int(const void *a, const void *b) { return (*(int*)a - *(int*)b); }

void print_plot(int arrival[], int end[], int n, int T) {
    int times[128], m = 0;
    times[m++] = 0; times[m++] = T;
    for (int i = 0; i < n; i++) { times[m++] = arrival[i]; times[m++] = end[i]; }
    qsort(times, m, sizeof(int), cmp_int);
    int unique[128], u = 0;
    for (int i = 0; i < m; i++) if (i == 0 || times[i] != times[i-1]) unique[u++] = times[i];
    printf("TIME NUMBER_IN_SYSTEM\n");
    for (int i = 0; i < u; i++) {
        int t = unique[i], count = 0;
        for (int j = 0; j < n; j++) if (arrival[j] <= t && end[j] > t) count++;
        printf("PLOT %d %d\n", t, count);
    }
    printf("OK: USE_THESE_POINTS_FOR_STEP_GRAPH\n");
}

int main(void) {
    int arrival[] = {0, 2, 6, 7, 9, 15};
    int end[]     = {2, 3, 9, 11, 12, 19};
    print_plot(arrival, end, 6, 19);
    return 0;
}
