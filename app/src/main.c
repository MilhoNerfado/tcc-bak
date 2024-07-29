/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
// #include <zephyr/drivers/sensor.h>

// #include <app/drivers/blink.h>
#include <app/drivers/mutex.h>

#include <app_version.h>


#define BLINK_PERIOD_MS_STEP 100U
#define BLINK_PERIOD_MS_MAX  1000U

int main(void) {
    int err;

    err = mutex_gpio_init();
    if (err < 0) {
        printk("ERROR: Failed to initialize mutex driver\n");
        return -1;
    }

    return 0;
}
