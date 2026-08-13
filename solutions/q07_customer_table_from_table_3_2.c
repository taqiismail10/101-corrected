#include <stdio.h>

void print_table(const char *title, int arrival[], int begin[], int end[], int n) {
    printf("CASE: %s\n", title);
    printf("CustomerID Interarrival Arrival-Time When-Server-Available Server-Chosen Service-Time Time-Service-Begins Waiting-Time-in-Queue Time-Service-Ends Time-Customer-Spends-in-System Server-Idle-Time\n");
    int prev_arrival = 0, prev_end = 0;
    for (int i = 0; i < n; i++) {
        int inter = (i == 0) ? 0 : arrival[i] - prev_arrival;
        int available = (i == 0) ? 0 : prev_end;
        int service = end[i] - begin[i];
        int wait = begin[i] - arrival[i];
        int system = end[i] - arrival[i];
        int idle = (i == 0) ? begin[i] : (begin[i] > prev_end ? begin[i] - prev_end : 0);
        printf("%d %d %d %d S1 %d %d %d %d %d %d\n", i+1, inter, arrival[i], available, service, begin[i], wait, end[i], system, idle);
        prev_arrival = arrival[i];
        prev_end = end[i];
    }
    printf("OK: TABLE_COMPLETED %d CUSTOMERS\n", n);
}

int main(void) {
    int arrival[] = {0, 1, 2, 8, 11, 18};
    int begin[]   = {0, 4, 6, 11, 15, 18};
    int end[]     = {4, 6, 11, 15, 16, 23};
    print_table("TEXTBOOK_TABLE_3_2", arrival, begin, end, 6);
    return 0;
}
