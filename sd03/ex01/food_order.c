#include "food_order.h"

int process_food_order(struct OrderRequest *request)
{
    int is_open = check_restaurant_status(request);
    struct Order *order = NULL;

    if (is_open) {
        order = create_standard_confirmation();
    } else {
        order = create_preorder_confirmation();
    }

    if (!order)
        return -1;

    send_confirmation_notification(order);
    free(order);

    return 0;
}