/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include "panoramix.h"

static void destroy_pthread(thread_params_t *lock_params)
{
    pthread_cond_destroy(&lock_params->cond_empty);
    pthread_cond_destroy(&lock_params->cond_full);
    pthread_mutex_destroy(&lock_params->lock_empty);
    pthread_mutex_destroy(&lock_params->lock_full);
}

static int exit_with_usage(const char *binary)
{
    printf("Usage: %s <nb_villagers> <pot_size> <nb_fights> <nb_refills>\n",
        binary);
    return 84;
}

int main(int argc, const char *argv[])
{
    params_t params = {};
    thread_params_t lock_params = {};

    if (!are_params_valid(argc, argv))
        return exit_with_usage(argv[0]);
    params = (params_t) {
        .nb_villagers = atoi(argv[1]),
        .pot_size = atoi(argv[2]),
        .nb_fights = atoi(argv[3]),
        .nb_refills = atoi(argv[4])
    };
    lock_params = (thread_params_t) {
        .cond_empty = PTHREAD_COND_INITIALIZER,
        .cond_full = PTHREAD_COND_INITIALIZER,
        .lock_empty = PTHREAD_MUTEX_INITIALIZER,
        .lock_full = PTHREAD_MUTEX_INITIALIZER
    };
    panoramix(&params, &lock_params);
    destroy_pthread(&lock_params);
}
