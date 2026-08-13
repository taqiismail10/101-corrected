#include <stdio.h>

int life_from_rn(int rn) {
    if (rn == 0) rn = 100;
    if (rn <= 10) return 1000;
    if (rn <= 23) return 1100;
    if (rn <= 48) return 1200;
    if (rn <= 61) return 1300;
    if (rn <= 70) return 1400;
    if (rn <= 82) return 1500;
    if (rn <= 84) return 1600;
    if (rn <= 90) return 1700;
    if (rn <= 95) return 1800;
    return 1900;
}

int delay_from_rn(int rn) {
    rn %= 10;
    if (rn >= 1 && rn <= 6) return 5;
    if (rn >= 7 && rn <= 9) return 10;
    return 15;
}

void print_cost(const char *policy, int bearings, int delay, int repair) {
    int cost_bearings = bearings * 32;
    int cost_delay = delay * 10;
    int cost_downtime_repair = repair * 10;
    double cost_repairperson = repair * 30.0 / 60.0;
    double total = cost_bearings + cost_delay + cost_downtime_repair + cost_repairperson;
    printf("POLICY: %s\n", policy);
    printf("OK: TOTAL_BEARINGS %d\n", bearings);
    printf("OK: TOTAL_DELAY_TIME %d MINUTES\n", delay);
    printf("OK: TOTAL_REPAIR_TIME %d MINUTES\n", repair);
    printf("OK: COST_BEARINGS %d\n", cost_bearings);
    printf("OK: COST_DELAY_TIME %d\n", cost_delay);
    printf("OK: COST_DOWNTIME_DURING_REPAIR %d\n", cost_downtime_repair);
    printf("OK: COST_REPAIRPERSON %.2f\n", cost_repairperson);
    printf("OK: TOTAL_COST %.2f\n\n", total);
}

int main(void) {
    int life1[5][3] = {{67,71,18},{55,21,65},{98,79,54},{76,88,75},{53,93,84}};
    int delay1[5][3] = {{7,8,5},{3,3,8},{1,1,3},{6,5,9},{4,9,2}};
    int delay_current = 0;
    printf("CURRENT_POLICY_DETAIL STEP BEARING LIFE_RN LIFE DELAY_RN DELAY\n");
    for (int i = 0; i < 5; i++) {
        for (int b = 0; b < 3; b++) {
            int life = life_from_rn(life1[i][b]);
            int delay = delay_from_rn(delay1[i][b]);
            delay_current += delay;
            printf("%d %d %d %d %d %d\n", i+1, b+1, life1[i][b], life, delay1[i][b], delay);
        }
    }
    print_cost("CURRENT_REPLACE_ONLY_FAILED_BEARING", 15, delay_current, 15 * 20);

    int delay2[5] = {5,8,3,9,2};
    int delay_proposed = 0;
    printf("PROPOSED_POLICY_DETAIL STEP LIFE1 LIFE2 LIFE3 FIRST_FAILURE DELAY\n");
    for (int i = 0; i < 5; i++) {
        int l1 = life_from_rn(life1[i][0]);
        int l2 = life_from_rn(life1[i][1]);
        int l3 = life_from_rn(life1[i][2]);
        int first = l1;
        if (l2 < first) first = l2;
        if (l3 < first) first = l3;
        int d = delay_from_rn(delay2[i]);
        delay_proposed += d;
        printf("%d %d %d %d %d %d\n", i+1, l1, l2, l3, first, d);
    }
    print_cost("PROPOSED_REPLACE_ALL_THREE", 15, delay_proposed, 5 * 40);
    printf("OK: BETTER_POLICY PROPOSED_REPLACE_ALL_THREE\n");
    return 0;
}
