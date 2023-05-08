/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** core logic
*/

#include <stdio.h>
#include <unistd.h>
#include "panoramix.h"

static const char *DRUID_WAKE_UP = "Druid: I'm ready... but sleepy...\n";
static const char *DRUID_REFILL = "Druid: Ah! Yes, yes, I'm awake! "
    "Working on it! Beware I can only make %ld more refills after this one.\n";
static const char *DRUID_SLEEP = "Druid: I'm out of viscum. "
    "I'm going back to... zZz\n";

static const char *VILLAGER_WAKE_UP = "Villager %ld: Going into battle!\n";
static const char *VILLAGER_DRINK = "Villager %ld: I need a drink... "
    "I see %ld servings left.\n";
static const char *VILLAGER_ASK_REFILL = "Villager %ld: "
    "Hey Pano wake up! We need more potion.\n";
static const char *VILLAGER_FIGHT = "Villager %ld: Take that roman scum! "
    "Only %ld left.\n";
static const char *VILLAGER_SLEEP = "Villager %ld: I'm going to sleep now.\n";

static void *druid(void *dparams)
{
    druid_data_t *data = (druid_data_t *)dparams;
    thread_params_t *threads = data->threads;

    printf(DRUID_WAKE_UP);
    while (data->nb_refills > 0) {
        pthread_mutex_lock(&threads->lock_full);
        pthread_cond_wait(&threads->cond_empty, &threads->lock_full);
        printf(DRUID_REFILL, data->nb_refills - 1);
        *(data->pot_size) = data->base_pot_size;
        data->nb_refills--;
        pthread_cond_signal(&threads->cond_full);
        pthread_mutex_unlock(&threads->lock_full);
    }
    printf(DRUID_SLEEP);
    return NULL;
}

static void *villager(void *vparams)
{
    villager_data_t *data = (villager_data_t *)vparams;
    thread_params_t *threads = data->threads;

    printf(VILLAGER_WAKE_UP, data->id);
    for (size_t i = 0; i < data->nb_fights; i++) {
        pthread_mutex_lock(&threads->lock_empty);
        printf(VILLAGER_DRINK, data->id, *data->pot_size);
        if (*data->pot_size == 0) {
            printf(VILLAGER_ASK_REFILL, data->id);
            pthread_cond_signal(&threads->cond_empty);
            pthread_cond_wait(&threads->cond_full, &threads->lock_full);
        }
        (*data->pot_size)--;
        printf(VILLAGER_FIGHT, data->id, data->nb_fights - i - 1);
        pthread_mutex_unlock(&threads->lock_empty);
    }
    printf(VILLAGER_SLEEP, data->id);
    return NULL;
}

void panoramix(params_t *params, thread_params_t *thread_params)
{
    pthread_t villager_threads[params->nb_villagers];
    villager_data_t villager_data[params->nb_villagers];
    pthread_t druid_thread;
    druid_data_t druid_data = { .pot_size = &params->pot_size,
        .base_pot_size = params->pot_size, .nb_refills = params->nb_refills,
        .threads = thread_params };

    pthread_create(&druid_thread, NULL, druid, &druid_data);
    sleep(1);
    for (size_t i = 0; i < params->nb_villagers; i++) {
        villager_data[i] = (villager_data_t) {
            .pot_size = &params->pot_size,
            .threads = thread_params,
            .nb_fights = params->nb_fights, .id = i
        };
        pthread_create(&villager_threads[i], NULL, villager, &villager_data[i]);
    }
    for (size_t i = 0; i < params->nb_villagers; i++)
        pthread_join(villager_threads[i], NULL);
    pthread_cancel(druid_thread);
}
