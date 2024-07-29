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
    printk("Zephyr Example Application %s\n", APP_VERSION_STRING);

    printk("Use the sensor to change LED blinking period\n");

    return 0;
}
