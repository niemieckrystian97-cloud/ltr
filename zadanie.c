#include <stdio.h>
#include "zadanie.h"

#define MAX_ITEMS 100



void calculate_order(OrderItem items[], int item_count, float tax_rate_percent, Order *order) {

    if (items == NULL || order == NULL || item_count <= 0) {
        return;
    }

    order->net_total = 0.0f;
    order->tax = 0.0f;
    order->total = 0.0f;

    for (int i = 0; i < item_count; i++) {
        items[i].net_total = items[i].net_price * items[i].quantity;
        items[i].total = items[i].net_total * (1 + tax_rate_percent / 100.0f);

        order->net_total += items[i].net_total;
        order->tax += items[i].net_total * (tax_rate_percent / 100.0f);
        order->total += items[i].total;
    }
}

void mainRun() {
    OrderItem items[MAX_ITEMS] = {
        {100.0f, 2, 0.0f, 0.0f},
        {50.0f, 3, 0.0f, 0.0f}
    };
    int item_count = 2;
    float tax_rate_percent = 23.0f; //przykładowy podatek

    Order order;
    calculate_order(items, item_count, tax_rate_percent, &order);



}

int main()
{
    mainRun();
}