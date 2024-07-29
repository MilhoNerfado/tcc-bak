//
// Created by milho on 7/29/24.
//

#ifndef APP_DRIVERS_MUTEX_H_
#define APP_DRIVERS_MUTEX_H_

#include <zephyr/device.h>
#include <zephyr/toolchain.h>

int mutex_gpio_init(void);

int mutex_set(uint32_t value);

#endif //APP_DRIVERS_MUTEX_H_
