#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int map_interarrival(int rn) { rn%=1000; if(rn<=125)return 1; if(rn<=250)return 2; if(rn<=375)return 3; if(rn<=500)return 4; if(rn<=625)return 5; if(rn<=750)return 6; if(rn<=875)return 7; return 8; }
int map_service(int rn) { rn%=100; if(rn==0)rn=100; if(rn<=10)return 1; if(rn<=30)return 2; if(rn<=60)return 3; if(rn<=85)return 4; if(rn<=95)return 5; return 6; }
unsigned int seed = 55555;
int rnd(int mod) { seed = seed * 1103515245u + 12345u; return (seed/65536u)%mod; }

int main(void) {
    int closing_time = 60 * 60; /* 60 hours in minutes */
    int arrival = 0, prev_end = 0, served = 0, total_wait = 0, total_service = 0;
    printf("CustomerID Arrival Service Begin Wait End Status\n");
    while (1) {
        int inter = (served == 0) ? 0 : map_interarrival(rnd(1000));
        arrival += inter;
        if (arrival > closing_time) break; /* no new customer after 60 hours */
        int service = map_service(rnd(100));
        int begin = arrival > prev_end ? arrival : prev_end;
        int wait = begin - arrival;
        int end = begin + service;
        served++;
        printf("%d %d %d %d %d %d ACCEPTED\n", served, arrival, service, begin, wait, end);
        total_wait += wait; total_service += service; prev_end = end;
    }
    printf("OK: SIMULATION_ACCEPTS_CUSTOMERS_UNTIL %d MINUTES\n", closing_time);
    printf("OK: LAST_DEPARTURE_AFTER_DRAINING_QUEUE %d MINUTES\n", prev_end);
    printf("OK: CUSTOMERS_SERVED %d\n", served);
    printf("OK: AVG_WAIT %.2f\n", served ? total_wait/(double)served : 0.0);
    printf("OK: SERVER_UTILIZATION_DURING_OPEN_PERIOD %.2f\n", total_service/(double)closing_time);
    return 0;
}
