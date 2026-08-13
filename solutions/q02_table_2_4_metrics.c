#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double mean_int(int a[], int n) {
    double s = 0;
    for (int i = 0; i < n; i++) s += a[i];
    return s / n;
}

double variance_int(int a[], int n) {
    double m = mean_int(a, n), s = 0;
    for (int i = 0; i < n; i++) s += (a[i] - m) * (a[i] - m);
    return s / n;
}

int cmp_int(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

double time_average(int start[], int end[], int n, int T) {
    int times[256], m = 0;
    times[m++] = 0;
    times[m++] = T;
    for (int i = 0; i < n; i++) {
        times[m++] = start[i];
        times[m++] = end[i];
    }
    qsort(times, m, sizeof(int), cmp_int);
    int unique[256], u = 0;
    for (int i = 0; i < m; i++) {
        if (i == 0 || times[i] != times[i - 1]) unique[u++] = times[i];
    }

    double area = 0.0;
    for (int i = 0; i < u - 1; i++) {
        int t1 = unique[i], t2 = unique[i + 1];
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (start[j] <= t1 && end[j] > t1) count++;
        }
        area += count * (t2 - t1);
    }
    return area / T;
}

void solve(const char *title, int arrival[], int begin[], int end[], int n) {
    int service[64], wait[64], system[64], inter[64];
    int waited = 0, total_service = 0, total_wait = 0, total_system = 0;
    int q_start[64], q_end[64], qn = 0;

    inter[0] = arrival[0];
    for (int i = 0; i < n; i++) {
        service[i] = end[i] - begin[i];
        wait[i] = begin[i] - arrival[i];
        system[i] = end[i] - arrival[i];
        if (i > 0) inter[i] = arrival[i] - arrival[i - 1];
        if (wait[i] > 0) {
            waited++;
            q_start[qn] = arrival[i];
            q_end[qn] = begin[i];
            qn++;
        }
        total_service += service[i];
        total_wait += wait[i];
        total_system += system[i];
    }

    int T = end[n - 1];
    double L = time_average(arrival, end, n, T);
    double Lq = qn ? time_average(q_start, q_end, qn, T) : 0.0;
    double util = (double)total_service / T;
    double var_inter = variance_int(inter + 1, n - 1);
    double var_service = variance_int(service, n);
    double var_system = variance_int(system, n);

    printf("CASE: %s\n", title);
    printf("CUSTOMER ARRIVAL BEGIN END SERVICE WAIT SYSTEM\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d %d %d %d %d %d\n", i + 1, arrival[i], begin[i], end[i], service[i], wait[i], system[i]);
    }

    printf("OK: WAITED_PERCENT %.2f\n", 100.0 * waited / n);
    printf("OK: SERVER_UTILIZATION %.2f\n", util);
    printf("OK: AVG_SYSTEM_TIME %.2f\n", (double)total_system / n);
    printf("OK: AVG_QUEUE_TIME %.2f\n", (double)total_wait / n);
    printf("OK: AVG_INTERARRIVAL_TIME %.2f\n", mean_int(inter + 1, n - 1));
    printf("OK: AVG_SERVICE_TIME %.2f\n", mean_int(service, n));
    printf("OK: EXPECTED_INTERARRIVAL_TIME %.2f\n", mean_int(inter + 1, n - 1));
    printf("OK: EXPECTED_SERVICE_TIME %.2f\n", mean_int(service, n));
    printf("OK: VAR_INTERARRIVAL %.2f STD_INTERARRIVAL %.2f\n", var_inter, sqrt(var_inter));
    printf("OK: VAR_SERVICE %.2f STD_SERVICE %.2f\n", var_service, sqrt(var_service));
    printf("OK: AVG_NUMBER_SYSTEM %.2f\n", L);
    printf("OK: AVG_NUMBER_QUEUE %.2f\n", Lq);

    if (waited > 0) {
        int waited_times[64], k = 0;
        for (int i = 0; i < n; i++) if (wait[i] > 0) waited_times[k++] = wait[i];
        double vw = variance_int(waited_times, k);
        printf("OK: AVG_WAIT_OF_WAITED %.2f STD_WAIT_OF_WAITED %.2f\n", mean_int(waited_times, k), sqrt(vw));
    } else {
        printf("OK: AVG_WAIT_OF_WAITED 0.00 STD_WAIT_OF_WAITED 0.00\n");
    }

    printf("OK: VAR_SYSTEM_TIME %.2f CV_SYSTEM_TIME %.2f\n", var_system,
           mean_int(system, n) == 0 ? 0.0 : sqrt(var_system) / mean_int(system, n));
}

int main(void) {
    int arrival[] = {0, 2, 6, 7, 9, 15};
    int begin[]   = {0, 2, 6, 9, 11, 15};
    int end[]     = {2, 3, 9, 11, 12, 19};
    solve("TEXTBOOK_TABLE_2_4", arrival, begin, end, 6);
    return 0;
}
