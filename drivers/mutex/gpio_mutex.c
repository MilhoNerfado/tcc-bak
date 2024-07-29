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


static int mutex_data_push(const bool data);

static struct self {
    bool is_init;
} self = {
    .is_init = false,
};

int mutex_gpio_init(void) {
    int err;

    if (self.is_init) {
        return 0;
    }

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

    self.is_init = true;

    return 0;
}

int mutex_set(uint32_t toggle) {
    if (!self.is_init) {
        return -ENOEXEC;
    }

    for (int i = 0; i < CONFIG_RELAY_LEN; ++i) {
        mutex_data_push(toggle & 1);
        toggle >>= 1;
    }

    /* TODO: toggle enable. Should check data sheet for behaviour */
    gpio_pin_set_dt(&enable_gpio, 0);
    gpio_pin_set_dt(&enable_gpio, 1);
    gpio_pin_set_dt(&enable_gpio, 0);

    return 0;
}

static int mutex_data_push(const bool data) {
    if (!self.is_init) {
        return -ENOEXEC;
    }

    gpio_pin_set_dt(&data_gpio, data);

    /* TODO: Toggle clock. Should check data sheet for behaviour */
    gpio_pin_set_dt(&clock_gpio, 1);
    gpio_pin_set_dt(&clock_gpio, 0);

    return 0;
}
