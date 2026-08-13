#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int interarrival(int rn) { rn%=100; if(rn==0)rn=100; if(rn<=25)return 1; if(rn<=65)return 2; if(rn<=85)return 3; return 4; }
int service_able(int rn) { rn%=100; if(rn==0)rn=100; if(rn<=30)return 2; if(rn<=58)return 3; if(rn<=83)return 4; return 5; }
int service_baker(int rn) { rn%=100; if(rn==0)rn=100; if(rn<=35)return 3; if(rn<=60)return 4; if(rn<=80)return 5; return 6; }
unsigned int seed = 24681357;
int rnd100(void) { seed = seed * 1103515245u + 12345u; return ((seed/65536u)%100) + 1; }

int main(int argc, char *argv[]) {
    int n = 100;
    for (int i = 1; i < argc; i++) if (!strcmp(argv[i], "--callers")) n = atoi(argv[++i]);
    if (n < 1 || n > 10000) { fprintf(stderr, "ERROR: E_RANGE: callers must be in 1..10000\n"); return 1; }
    int arrival = 0, able_free = 0, baker_free = 0;
    int able_busy = 0, baker_busy = 0, total_wait = 0, total_system = 0, able_count = 0, baker_count = 0;
    printf("Caller Interarrival Arrival Server Service Begin Wait End System\n");
    for (int i = 1; i <= n; i++) {
        int ia = (i == 1) ? 0 : interarrival(rnd100());
        arrival += ia;
        int server, service, begin, end;
        if (able_free <= arrival) {
            server = 1; service = service_able(rnd100()); begin = arrival; end = begin + service; able_free = end; able_busy += service; able_count++;
        } else if (baker_free <= arrival) {
            server = 2; service = service_baker(rnd100()); begin = arrival; end = begin + service; baker_free = end; baker_busy += service; baker_count++;
        } else if (able_free <= baker_free) {
            server = 1; service = service_able(rnd100()); begin = able_free; end = begin + service; able_free = end; able_busy += service; able_count++;
        } else {
            server = 2; service = service_baker(rnd100()); begin = baker_free; end = begin + service; baker_free = end; baker_busy += service; baker_count++;
        }
        int wait = begin - arrival;
        total_wait += wait; total_system += end - arrival;
        printf("%d %d %d %s %d %d %d %d %d\n", i, ia, arrival, server==1?"ABLE":"BAKER", service, begin, wait, end, end-arrival);
    }
    int final_time = able_free > baker_free ? able_free : baker_free;
    printf("OK: ABLE_CALLS %d BAKER_CALLS %d\n", able_count, baker_count);
    printf("OK: AVG_CALLER_DELAY %.2f\n", total_wait/(double)n);
    printf("OK: AVG_SYSTEM_TIME %.2f\n", total_system/(double)n);
    printf("OK: ABLE_UTILIZATION %.2f\n", able_busy/(double)final_time);
    printf("OK: BAKER_UTILIZATION %.2f\n", baker_busy/(double)final_time);
    return 0;
}
