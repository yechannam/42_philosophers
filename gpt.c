#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define MAX_MEALS 10

pthread_t philosophers[NUM_PHILOSOPHERS];
pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];
int meals_eaten[NUM_PHILOSOPHERS];

void *philosopher(void *arg)
{
    int id = *(int *)arg;
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;
    int meals = 0;

    while (meals < MAX_MEALS)
    {
        // Think
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // Try to pick up left chopstick
        pthread_mutex_lock(&chopsticks[left_chopstick]);
        printf("Philosopher %d picked up left chopstick %d\n", id, left_chopstick);

        // Try to pick up right chopstick
        pthread_mutex_lock(&chopsticks[right_chopstick]);
        printf("Philosopher %d picked up right chopstick %d\n", id, right_chopstick);

        // Eat
        printf("Philosopher %d is eating\n", id);
        meals++;
        meals_eaten[id]++;
        sleep(1);

        // Release chopsticks
        printf("Philosopher %d is releasing chopsticks\n", id);
        pthread_mutex_unlock(&chopsticks[left_chopstick]);
        pthread_mutex_unlock(&chopsticks[right_chopstick]);
    }

    printf("Philosopher %d finished %d meals\n", id, meals);
    return NULL;
}

int main()
{
    // Initialize mutex locks and start philosophers
    int i;
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_init(&chopsticks[i], NULL);
        meals_eaten[i] = 0;
        pthread_create(&philosophers[i], NULL, philosopher, &i);
    }

    // Wait for philosophers to finish
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Print meals eaten by each philosopher
    printf("Meals eaten:\n");
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        printf("Philosopher %d: %d\n", i, meals_eaten[i]);
    }

    // Destroy mutex locks
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}
