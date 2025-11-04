typedef struct {
    float net_price;
    unsigned int quantity;
    float net_total;
    float total;
} OrderItem;

typedef struct {
    float net_total;
    float tax;
    float total;
} Order;
void calculate_order(OrderItem items[], int item_count, float tax_rate_percent, Order *order);