/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

#include <app/drivers/mutex.h>
#include <zephyr/shell/shell.h>


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

static int cmd_mutex_clear(const struct shell *sh, size_t argc, char **argv) {
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);
    printk("CLEAR COMMAND\n");
    return mutex_gpio_clear();
}

static int cmd_mutex_set(const struct shell *sh, size_t argc, char **argv) {
    printk("SET COMMAND\n");
    if (argc != 1) {
        printk("ERROR: \n");
        return -EIO;
    }

    return mutex_gpio_clear(); /* TODO: change to a mutex_gpio_set */
}


/* Creating subcommands (level 1 command) array for command "demo". */
SHELL_STATIC_SUBCMD_SET_CREATE(sub_mutex,
                               SHELL_CMD(clear, NULL, "Clear mutex", cmd_mutex_clear),
                               SHELL_CMD(set, NULL, "Set mutex", cmd_mutex_set),
                               SHELL_SUBCMD_SET_END
);
/* Creating root (level 0) command "demo" */
SHELL_CMD_REGISTER(mutex, &sub_mutex, "Demo commands", NULL);
