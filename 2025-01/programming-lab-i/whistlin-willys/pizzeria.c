#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#define PIZZA_CHEFS 5
#define OVENS 3

pthread_mutex_t output_mtx;
pthread_mutex_t consumer_mtx;
sem_t available_pizzas_sem;

int pizza_buffer[OVENS] = {0};
int score[PIZZA_CHEFS] = {0};

int get_random_time_in_ms()
{
    return (rand() % 26 + 5) * 100; // min. 500ms, max. 3000ms
}

void sleep_random(unsigned long time_in_ms)
{
    struct timespec ts;
    ts.tv_sec = time_in_ms / 1000;
    ts.tv_nsec = (time_in_ms % 1000) * 1000000UL;

    nanosleep(&ts, NULL);
}

void show_buffer()
{
    int i;

    pthread_mutex_lock(&output_mtx); // enter critical region

    printf("\nPIZZA BUFFER\n");

    for (i = 0; i < OVENS; ++i) {
        printf("[OVEN %d] = %d | ", i, pizza_buffer[i]);
    }

    printf("\n\nSCORE\n");

    for (i = 0; i < PIZZA_CHEFS; ++i) {
        printf("[CHEF %d] = %d | ", i, score[i]);
    }

    printf("\n\n");

    pthread_mutex_unlock(&output_mtx); // exit critical region
}

void *oven (void *arg)
{
    int oven_idx = *(int *) arg;
    int sleep_time_in_ms;

    printf("Oven(%d) is READY\n", oven_idx);

    while (1)
    {
        sleep_time_in_ms = get_random_time_in_ms();

        // produce time
        sleep_random(sleep_time_in_ms);

        pthread_mutex_lock(&output_mtx); // enter critical region
        printf("\n[PRODUCER] Oven(%d) produced 1 pizza | duration: %dms\n", oven_idx, sleep_time_in_ms);
        pthread_mutex_unlock(&output_mtx); // exit critical region

        pizza_buffer[oven_idx] += 1;
        sem_post(&available_pizzas_sem);
    }
}

void *chef (void *arg)
{
    int i;
    int chef_idx = *(int *) arg;
    int sleep_time_in_ms;

    printf("Chef(%d) is READY\n", chef_idx);

    while (1)
    {
        sleep_time_in_ms = get_random_time_in_ms();

        // wait until there are pizzas available
        sem_wait(&available_pizzas_sem);

        pthread_mutex_lock(&consumer_mtx); // enter critical region

        int random_search_start = rand() % OVENS;

        for (i = 0; i < OVENS; ++i) {
            int idx = (random_search_start + i) % OVENS;
            int pizzas = pizza_buffer[idx];

            if (pizzas == 0) continue;

            pthread_mutex_lock(&output_mtx);
            printf("\n[CONSUMER] Chef(%d) is consuming 1 pizza | duration: %dms\n", chef_idx, sleep_time_in_ms);
            printf("- Oven(%d) had %d pizzas, now has %d pizzas\n", idx, pizzas, pizzas-1);
            pthread_mutex_unlock(&output_mtx);

            // consume pizza
            pizza_buffer[idx] -= 1;
            score[chef_idx] += 1;
            show_buffer();

            break;
        }
        pthread_mutex_unlock(&consumer_mtx); // exit critical region

        // consume time
        sleep_random(sleep_time_in_ms);
    }
}

void init_threads(pthread_t threads[], int ids[], int count, void *(*routine)(void *));
void join_threads(pthread_t threads[], int count);

void init_synchronization_tools();
void destroy_synchronization_tools();

int main(int argc, char **argv)
{
    printf("+------------------------------+\n");
    printf("| WELCOME TO WHISTLIN\' WILLY\'S |\n");
    printf("+------------------------------+\n");

    srand(time(NULL));

    init_synchronization_tools();

    pthread_t chefs[PIZZA_CHEFS];
    int chefs_ids[PIZZA_CHEFS];

    pthread_t ovens[OVENS];
    int ovens_ids[OVENS];

    init_threads(chefs, chefs_ids, PIZZA_CHEFS, chef);
    init_threads(ovens, ovens_ids, OVENS, oven);

    join_threads(ovens, OVENS);
    join_threads(chefs, PIZZA_CHEFS);

    destroy_synchronization_tools();

    return 0;
}

void init_threads(pthread_t threads[], int ids[], int count, void *(*routine)(void *))
{
    int i, result;

    for (i = 0; i < count; ++i) {
        ids[i] = i;

        result = pthread_create(
            &threads[i],
            NULL,
            routine,
            &ids[i]
        );

        if (result != 0) {
            perror("\nError creating thread\n");
            exit(EXIT_FAILURE);
        }
    }
}

void join_threads(pthread_t threads[], int count)
{
    int i, result;

    for (i = 0; i < count; ++i) {
        result = pthread_join(threads[i], NULL);

        if (result != 0) {
            perror("\nError waiting thread to finish\n");
            exit(EXIT_FAILURE);
        }
    }
}

void init_synchronization_tools()
{
    pthread_mutex_init(&consumer_mtx, NULL);
    pthread_mutex_init(&output_mtx, NULL);
    sem_init(&available_pizzas_sem, 0, 0);
}

void destroy_synchronization_tools()
{
    pthread_mutex_destroy(&consumer_mtx);
    pthread_mutex_destroy(&output_mtx);
    sem_destroy(&available_pizzas_sem);
}

