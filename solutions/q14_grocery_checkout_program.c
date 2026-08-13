#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int map_interarrival(int rn) {
    rn %= 1000;
    if (rn <= 125) return 1; if (rn <= 250) return 2; if (rn <= 375) return 3; if (rn <= 500) return 4;
    if (rn <= 625) return 5; if (rn <= 750) return 6; if (rn <= 875) return 7; return 8;
}
int map_service(int rn) {
    rn %= 100; if (rn == 0) rn = 100;
    if (rn <= 10) return 1; if (rn <= 30) return 2; if (rn <= 60) return 3;
    if (rn <= 85) return 4; if (rn <= 95) return 5; return 6;
}
unsigned int seed = 12345;
int rnd(int mod) { seed = seed * 1103515245u + 12345u; return (seed / 65536u) % mod; }

int main(int argc, char *argv[]) {
    int n = 100;
    for (int i = 1; i < argc; i++) if (!strcmp(argv[i], "--customers")) n = atoi(argv[++i]);
    if (n < 1 || n > 10000) { fprintf(stderr, "ERROR: E_RANGE: customers must be in 1..10000\n"); return 1; }

    int arrival = 0, prev_end = 0, waited = 0, total_wait = 0, total_sys = 0, total_service = 0, total_idle = 0;
    printf("CustomerID Interarrival Arrival Service Begin Wait End System Idle\n");
    for (int i = 1; i <= n; i++) {
        int inter = (i == 1) ? 0 : map_interarrival(rnd(1000));
        int service = map_service(rnd(100));
        arrival += inter;
        int begin = arrival > prev_end ? arrival : prev_end;
        int wait = begin - arrival;
        int end = begin + service;
        int idle = begin > prev_end ? begin - prev_end : 0;
        printf("%d %d %d %d %d %d %d %d %d\n", i, inter, arrival, service, begin, wait, end, end-arrival, idle);
        if (wait > 0) waited++;
        total_wait += wait; total_sys += end - arrival; total_service += service; total_idle += idle; prev_end = end;
    }
    printf("OK: AVG_WAIT %.2f\n", total_wait/(double)n);
    printf("OK: PROBABILITY_WAIT %.2f\n", waited/(double)n);
    printf("OK: SERVER_UTILIZATION %.2f\n", total_service/(double)prev_end);
    printf("OK: AVG_SYSTEM_TIME %.2f\n", total_sys/(double)n);
    printf("OK: TOTAL_IDLE_TIME %d\n", total_idle);
    return 0;
}
