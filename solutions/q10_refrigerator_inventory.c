#include <stdio.h>

int map_demand(int rn) {
    if (rn == 0) rn = 100;
    if (rn <= 10) return 0;
    if (rn <= 35) return 1;
    if (rn <= 70) return 2;
    if (rn <= 91) return 3;
    return 4;
}

int map_lead(int rn) {
    rn %= 10;
    if (rn >= 1 && rn <= 6) return 1;
    if (rn >= 7 && rn <= 9) return 2;
    return 3;
}

int main(void) {
    int demand_rn[25] = {26,68,33,95,86,11,64,79,55,34,21,44,90, 0,36, 8,80,51,81,53,15,73,19,19,44};
    int lead_rn[5] = {5, 0, 3, 4, 7};
    int M = 11, N = 5;
    int inventory = 3, shortage = 0;
    int order_qty = 8, days_until_arrival = 2;
    int lead_index = 0;
    int total_ending = 0, total_demand = 0, total_shortage = 0;

    printf("DAY CYCLE DAY_IN_CYCLE BEGIN_INV RN_DEMAND DEMAND END_INV SHORTAGE ORDER_QTY RN_LEAD LEAD DAYS_UNTIL_ARRIVAL\n");
    for (int day = 1; day <= 25; day++) {
        int cycle = (day - 1) / N + 1;
        int day_in_cycle = (day - 1) % N + 1;
        if (days_until_arrival == 0 && order_qty > 0) {
            inventory += order_qty;
            order_qty = 0;
        }
        int begin_inv = inventory;
        int demand = map_demand(demand_rn[day - 1]);
        total_demand += demand;

        if (inventory >= demand) {
            inventory -= demand;
            shortage = 0;
        } else {
            shortage = demand - inventory;
            inventory = 0;
        }
        total_ending += inventory;
        total_shortage += shortage;

        int rn_lead = -1, lead = -1, placed_order = 0;
        if (day_in_cycle == N) {
            placed_order = M - inventory + shortage;
            order_qty = placed_order;
            rn_lead = lead_rn[lead_index++ % 5];
            lead = map_lead(rn_lead);
            days_until_arrival = lead;
        }

        printf("%d %d %d %d %02d %d %d %d %d ", day, cycle, day_in_cycle, begin_inv, demand_rn[day-1], demand, inventory, shortage, placed_order);
        if (rn_lead >= 0) printf("%d %d %d\n", rn_lead, lead, days_until_arrival);
        else printf("- - %d\n", days_until_arrival);

        if (days_until_arrival > 0) days_until_arrival--;
    }

    printf("OK: AVG_ENDING_INVENTORY %.2f\n", total_ending / 25.0);
    printf("OK: AVG_DEMAND %.2f\n", total_demand / 25.0);
    printf("OK: AVG_SHORTAGE %.2f\n", total_shortage / 25.0);
    printf("OK: IMPROVE_BY choosing better M,N, reducing lead time, reducing demand variability, and preventing shortage/lost sales.\n");
    return 0;
}
