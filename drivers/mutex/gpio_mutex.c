/*
 * Copyright (c) 2024 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT mutex_gpio_led

#include <zephyr/device.h>

#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#include <app/drivers/mutex.h>


const struct gpio_dt_spec enable_gpio = GPIO_DT_SPEC_GET(DT_NODELABEL(mutex), enable_gpios);
const struct gpio_dt_spec clock_gpio = GPIO_DT_SPEC_GET(DT_NODELABEL(mutex), clock_gpios);
const struct gpio_dt_spec data_gpio = GPIO_DT_SPEC_GET(DT_NODELABEL(mutex), data_gpios);
const struct gpio_dt_spec reset_gpio = GPIO_DT_SPEC_GET(DT_NODELABEL(mutex), reset_gpios);

int mutex_gpio_init(void) {
    int err;
    if (!gpio_is_ready_dt(&enable_gpio)) {
        return -ENODEV;
    }

    if (!gpio_is_ready_dt(&clock_gpio)) {
        return -ENODEV;
    }

    if (!gpio_is_ready_dt(&data_gpio)) {
        return -ENODEV;
    }

    if (!gpio_is_ready_dt(&reset_gpio)) {
        return -ENODEV;
    }

    err = gpio_pin_configure_dt(&enable_gpio, GPIO_OUTPUT_INACTIVE);
    if (err < 0) {
        return err;
    }

    err = gpio_pin_configure_dt(&clock_gpio, GPIO_OUTPUT_INACTIVE);
    if (err < 0) {
        return err;
    }

    err = gpio_pin_configure_dt(&data_gpio, GPIO_OUTPUT_INACTIVE);
    if (err < 0) {
        return err;
    }

    err = gpio_pin_configure_dt(&reset_gpio, GPIO_OUTPUT_INACTIVE);
    if (err < 0) {
        return err;
    }

    return 0;
}
