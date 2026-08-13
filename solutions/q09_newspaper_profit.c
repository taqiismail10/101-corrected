#include <stdio.h>

int map_newsday(int rn) {
    if (rn == 0) rn = 100;
    if (rn <= 35) return 0; /* Good */
    if (rn <= 80) return 1; /* Fair */
    return 2;               /* Poor */
}

int map_demand(int type, int rn) {
    if (rn == 0) rn = 100;
    int cum[3][7] = {
        {3, 8, 23, 43, 78, 93, 100},
        {10, 28, 68, 88, 96, 100, 100},
        {44, 66, 82, 94, 100, 100, 100}
    };
    int demand[7] = {40, 50, 60, 70, 80, 90, 100};
    for (int i = 0; i < 7; i++) if (rn <= cum[type][i]) return demand[i];
    return 100;
}

int main(void) {
    int news_rn[20]   = {58,17,21,45,43,36,27,73,86,19,93,45,47,30,12,41,65,57,18,98};
    int demand_rn[20] = {93,63,31,19,91,75,84,37,23, 2,53,96,33,86,16, 7,64,94,55,13};
    const char *type_name[] = {"GOOD", "FAIR", "POOR"};
    int buy = 70;
    int buy_cost = 33, sell_price = 50, scrap_price = 5;
    int total_profit = 0;

    printf("DAY RN_TYPE TYPE RN_DEMAND DEMAND SOLD SCRAP PROFIT_CENTS\n");
    for (int i = 0; i < 20; i++) {
        int type = map_newsday(news_rn[i]);
        int demand = map_demand(type, demand_rn[i]);
        int sold = demand < buy ? demand : buy;
        int scrap = buy - sold;
        int profit = sold * sell_price + scrap * scrap_price - buy * buy_cost;
        total_profit += profit;
        printf("%d %02d %s %02d %d %d %d %d\n", i+1, news_rn[i], type_name[type], demand_rn[i], demand, sold, scrap, profit);
    }
    printf("OK: TOTAL_PROFIT_CENTS %d\n", total_profit);
    printf("OK: TOTAL_PROFIT_DOLLARS %.2f\n", total_profit / 100.0);
    return 0;
}
