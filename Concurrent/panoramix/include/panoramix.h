/*
** EPITECH PROJECT, 2023
** include
** File description:
** $DESCRIPTION
*/

#pragma once

#include <pthread.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct params_s {
    size_t nb_villagers;
    size_t pot_size;
    size_t nb_fights;
    size_t nb_refills;
} params_t;

typedef struct thread_params_s {
    pthread_cond_t cond_empty;
    pthread_cond_t cond_full;
    pthread_mutex_t lock_empty;
    pthread_mutex_t lock_full;
} thread_params_t;

typedef struct villager_data_s {
    size_t *pot_size;
    thread_params_t *threads;
    size_t nb_fights;
    size_t id;
} villager_data_t;

typedef struct druid_data_s {
    size_t *pot_size;
    size_t base_pot_size;
    size_t nb_refills;
    thread_params_t *threads;
} druid_data_t;


bool are_params_valid(int argc, const char *argv[]);

void panoramix(params_t *params, thread_params_t *thread_params);
