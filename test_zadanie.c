#include "unity.h"
#include "zadanie.h"

void setUp(void) {}
void tearDown(void) {}

void test_single_item_should_calculate_correct_totals(void) {
    OrderItem items[1] = {
        { .net_price = 100.0f, .quantity = 2 }
    };
    Order order;

    calculate_order(items, 1, 23.0f, &order);

    TEST_ASSERT_FLOAT(200.0f, items[0].net_total);
    TEST_ASSERT_FLOAT(246.0f, items[0].total);

    TEST_ASSERT_FLOAT(200.0f, order.net_total);
    TEST_ASSERT_FLOAT(46.0f, order.tax);
    TEST_ASSERT_FLOAT(246.0f, order.total);
}

void test_multiple_items_should_accumulate_totals(void) {
    OrderItem items[2] = {
        { .net_price = 50.0f, .quantity = 1 },
        { .net_price = 30.0f, .quantity = 3 }
    };
    Order order;

    calculate_order(items, 2, 10.0f, &order);

    TEST_ASSERT_FLOAT(50.0f, items[0].net_total);
    TEST_ASSERT_FLOAT(55.0f, items[0].total);
    TEST_ASSERT_FLOAT(90.0f, items[1].net_total);
    TEST_ASSERT_FLOAT(99.0f, items[1].total);

    TEST_ASSERT_FLOAT(140.0f, order.net_total);
    TEST_ASSERT_FLOAT(14.0f, order.tax);
    TEST_ASSERT_FLOAT(154.0f, order.total);
}

void test_zero_quantity_should_result_in_zero_totals(void) {
    OrderItem items[1] = {
        { .net_price = 100.0f, .quantity = 0 }
    };
    Order order;

    calculate_order(items, 1, 20.0f, &order);

    TEST_ASSERT_FLOAT(0.0f, items[0].net_total);
    TEST_ASSERT_FLOAT(0.0f, items[0].total);

    TEST_ASSERT_FLOAT(0.0f, order.net_total);
    TEST_ASSERT_FLOAT(0.0f, order.tax);
    TEST_ASSERT_FLOAT(0.0f, order.total);
}

void test_zero_tax_should_not_affect_totals(void) {
    OrderItem items[1] = {
        { .net_price = 100.0f, .quantity = 1 }
    };
    Order order;

    calculate_order(items, 1, 0.0f, &order);

    TEST_ASSERT_FLOAT(100.0f, items[0].net_total);
    TEST_ASSERT_FLOAT(100.0f, items[0].total);

    TEST_ASSERT_FLOAT(100.0f, order.net_total);
    TEST_ASSERT_FLOAT(0.0f, order.tax);
    TEST_ASSERT_FLOAT(100.0f, order.total);
}

void test_null_items_should_not_crash(void) {
    Order order = { .net_total = -1.0f, .tax = -1.0f, .total = -1.0f };

    calculate_order(NULL, 1, 10.0f, &order);

    TEST_ASSERT_FLOAT(-1.0f, order.net_total);
    TEST_ASSERT_FLOAT(-1.0f, order.tax);
    TEST_ASSERT_FLOAT(-1.0f, order.total);
}

void test_null_order_should_not_crash(void) {
    OrderItem items[1] = {
        { .net_price = 100.0f, .quantity = 1 }
    };

    calculate_order(items, 1, 10.0f, NULL);

    TEST_ASSERT_FLOAT(100.0f, items[0].net_total);
    TEST_ASSERT_FLOAT(110.0f, items[0].total);
}

void test_zero_items_should_not_modify_order(void) {
    OrderItem items[1] = {
        { .net_price = 100.0f, .quantity = 1 }
    };
    Order order = { .net_total = -1.0f, .tax = -1.0f, .total = -1.0f };

    calculate_order(items, 0, 10.0f, &order);

    TEST_ASSERT_FLOAT(-1.0f, order.net_total);
    TEST_ASSERT_FLOAT(-1.0f, order.tax);
    TEST_ASSERT_FLOAT(-1.0f, order.total);
}
