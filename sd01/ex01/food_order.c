#include "food_order.h"

int process_food_order(struct OrderRequest *request)
{
    int is_open = check_restaurant_status(request);

    if (is_open)
    {
        struct Order *order = create_standard_confirmation();
        if (!order)
            return -1;
    }
    else
    {
        struct Order *order = create_preorder_confirmation();
        if (!order)
            return -1;
    }

    send_confirmation_notification(order);
    
    free(order);
    return 0;
}