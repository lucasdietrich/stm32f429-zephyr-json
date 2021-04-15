#include <zephyr.h>

#include "struct_json.h"

void main(void)
{
    json_do_buf();

    k_sleep(K_MSEC(1000));

    json_do_cb();

    k_sleep(K_FOREVER);
}
