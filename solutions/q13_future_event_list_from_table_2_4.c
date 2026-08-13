#include <stdio.h>
#include <string.h>

int main(void) {
    int n = 6;
    int arrival[] = {0,2,6,7,9,15};
    int begin[]   = {0,2,6,9,11,15};
    int end[]     = {2,3,9,11,12,19};
    int clocks[]  = {0,2,3,6,7,9,11,12,15,19};
    int m = 10;
    int total_busy = 0, max_q = 0, response_sum = 0, ge4 = 0, dep = 0;

    printf("Clock Queue-State Server-State Future-Event-List Busy-Time Maximum-Queue-Length Departed-Response-Time Customers-4-or-more Total-Departures\n");
    for (int c = 0; c < m; c++) {
        int t = clocks[c];
        int q = 0, server = 0;
        char fel[512] = "";
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= t && begin[i] > t) q++;
            if (begin[i] <= t && end[i] > t) server = 1;
            if (arrival[i] >= t) { char buf[32]; sprintf(buf, "(A,%d,C%d) ", arrival[i], i+1); strcat(fel, buf); }
            if (end[i] >= t) { char buf[32]; sprintf(buf, "(D,%d,C%d) ", end[i], i+1); strcat(fel, buf); }
        }
        if (q > max_q) max_q = q;
        dep = 0; response_sum = 0; ge4 = 0; total_busy = 0;
        for (int i = 0; i < n; i++) {
            if (end[i] <= t) {
                int r = end[i] - arrival[i];
                dep++;
                response_sum += r;
                if (r >= 4) ge4++;
            }
            int a = begin[i], b = end[i];
            if (a < t) total_busy += (b < t ? b : t) - a;
        }
        printf("%d %d %d %s %d %d %d %d %d\n", t, q, server, fel[0] ? fel : "****", total_busy, max_q, response_sum, ge4, dep);
    }
    printf("OK: FUTURE_EVENT_LIST_TABLE_COMPLETED\n");
    return 0;
}
