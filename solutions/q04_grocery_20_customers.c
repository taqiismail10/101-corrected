#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int map_interarrival(int rn) {
    rn %= 1000;
    if (rn <= 125) return 1;
    if (rn <= 250) return 2;
    if (rn <= 375) return 3;
    if (rn <= 500) return 4;
    if (rn <= 625) return 5;
    if (rn <= 750) return 6;
    if (rn <= 875) return 7;
    return 8;
}

int map_service(int rn) {
    rn %= 100;
    if (rn == 0) rn = 100;
    if (rn <= 10) return 1;
    if (rn <= 30) return 2;
    if (rn <= 60) return 3;
    if (rn <= 85) return 4;
    if (rn <= 95) return 5;
    return 6;
}

double mean(int a[], int n) { double s = 0; for (int i = 0; i < n; i++) s += a[i]; return s / n; }
double var(int a[], int n) { double m = mean(a,n), s = 0; for (int i = 0; i < n; i++) s += (a[i]-m)*(a[i]-m); return s / n; }

int main(void) {
    int n = 20;
    int inter_rn[20] = {0,64,112,678,289,871,583,139,423,39,413,462,843,738,359,888,902,212,477,991};
    int serv_rn[20]  = {84,18,76,82,56,30,5,92,55,25,94,32,71,46,69,27,80,61,47,10};
    int inter[20], service[20], arrival[20], begin[20], end[20], wait[20], system[20];
    int total_wait = 0, total_sys = 0, waited = 0, total_service = 0;

    arrival[0] = 0;
    for (int i = 0; i < n; i++) {
        inter[i] = (i == 0) ? 0 : map_interarrival(inter_rn[i]);
        service[i] = map_service(serv_rn[i]);
        if (i > 0) arrival[i] = arrival[i - 1] + inter[i];
        begin[i] = (i == 0 || arrival[i] > end[i - 1]) ? arrival[i] : end[i - 1];
        end[i] = begin[i] + service[i];
        wait[i] = begin[i] - arrival[i];
        system[i] = end[i] - arrival[i];
        total_wait += wait[i];
        total_sys += system[i];
        total_service += service[i];
        if (wait[i] > 0) waited++;
    }

    printf("CUSTOMER IA_RN INTERARRIVAL ARRIVAL SERV_RN SERVICE BEGIN WAIT END SYSTEM\n");
    for (int i = 0; i < n; i++) {
        printf("%d %03d %d %d %02d %d %d %d %d %d\n", i+1, inter_rn[i], inter[i], arrival[i], serv_rn[i], service[i], begin[i], wait[i], end[i], system[i]);
    }
    printf("OK: WAITED_PERCENT %.2f\n", 100.0 * waited / n);
    printf("OK: SERVER_UTILIZATION %.2f\n", (double)total_service / end[n-1]);
    printf("OK: AVG_SYSTEM_TIME %.2f\n", (double)total_sys / n);
    printf("OK: AVG_QUEUE_TIME %.2f\n", (double)total_wait / n);
    printf("OK: EXPECTED_INTERARRIVAL 4.50 VAR_INTERARRIVAL 5.25 STD_INTERARRIVAL %.2f CV_INTERARRIVAL %.2f\n", sqrt(5.25), sqrt(5.25)/4.5);

    int service_values[] = {1,2,3,4,5,6};
    double p[] = {0.10,0.20,0.30,0.25,0.10,0.05};
    double es = 0, es2 = 0;
    for (int i = 0; i < 6; i++) { es += service_values[i] * p[i]; es2 += service_values[i] * service_values[i] * p[i]; }
    double vs = es2 - es * es;
    printf("OK: EXPECTED_SERVICE %.2f VAR_SERVICE %.2f STD_SERVICE %.2f CV_SERVICE %.2f\n", es, vs, sqrt(vs), sqrt(vs)/es);
    return 0;
}
