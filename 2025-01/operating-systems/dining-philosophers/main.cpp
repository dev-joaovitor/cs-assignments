// use std 23

#include <iostream>
#include <semaphore>
#include <mutex>
#include <thread>
#include <chrono>
#include <random>

#define N_OF_PHILOSOPHERS 5 // number of chopsticks as well

enum class State
{
    THINKING = 0,
    HUNGRY = 1,
    EATING = 2,
};

/*
 * position of the left neighbor of i-th philosopher
 */
size_t inline left(size_t i)
{
    /*
     * add number of philosophers in case i - 1 is negative
     */
    return (i - 1 + N_OF_PHILOSOPHERS) % N_OF_PHILOSOPHERS;
    // 0 - 1 + 5 = 4 -> 4 % 5 = 4
    // 1 - 1 + 5 = 5 -> 5 % 5 = 0
    // 2 - 1 + 5 = 6 -> 6 % 5 = 1
    // 3 - 1 + 5 = 7 -> 5 % 5 = 2
    // 4 - 1 + 5 = 8 -> 8 % 5 = 3
}

/*
 * position of the right neighbor of i-th philosopher
 */
size_t inline right(size_t i)
{
    return (i + 1) % N_OF_PHILOSOPHERS;
    // 0 + 1 = 1 -> 1 % 5 = 1
    // 1 + 1 = 2 -> 2 % 5 = 2
    // 2 + 1 = 3 -> 3 % 5 = 3
    // 3 + 1 = 4 -> 4 % 5 = 4
    // 4 + 1 = 5 -> 5 % 5 = 0
}

State state[N_OF_PHILOSOPHERS];

/*
 * mutual exclusion for picking up and putting down forks
 */
std::mutex critical_region_mtx;

/*
 * mutual exclusion for output synchronization
 */
std::mutex output_mtx;

/*
 * array of semaphores, one semaphore per philosopher.
 * acquired semaphore means i-th philosopher has 2 chopsticks.
 */
std::binary_semaphore both_chopsticks_available[N_OF_PHILOSOPHERS]
{
    std::binary_semaphore{0}, std::binary_semaphore{0},
    std::binary_semaphore{0}, std::binary_semaphore{0},
    std::binary_semaphore{0}
};

size_t get_random_value_between(size_t min, size_t max)
{
    static std::mt19937 rnd(std::time(nullptr));
    return std::uniform_int_distribution<>(min, max)(rnd);
}

/*
 * think for a random period of time
 */
void think(size_t position)
{
    size_t duration_in_ms = get_random_value_between(400, 800);

    { // enter critical region
        std::lock_guard<std::mutex> guard(output_mtx);
        std::cout << position << " is THINKING " << duration_in_ms << "ms\n";
    } // exit critical region

    std::this_thread::sleep_for(std::chrono::milliseconds(duration_in_ms));
}

inline bool neighbors_are_not_eating(size_t position)
{
    return state[left(position)] != State::EATING &&
        state[right(position)] != State::EATING;
}

/*
 * test if philosopher in the
 * given position can eat
 */
void try_to_eat(size_t position)
{
    if (state[position] == State::HUNGRY 
        && neighbors_are_not_eating(position))
    {
        state[position] = State::EATING;
        both_chopsticks_available[position].release();
    }
}

/*
 * take both chopsticks if they are available
 */
void take_chopsticks(size_t position)
{
    { // enter test critical region
        std::lock_guard<std::mutex> test_guard(critical_region_mtx);
        state[position] = State::HUNGRY;

        { // enter output critical region
            std::lock_guard<std::mutex> out_guard(output_mtx);
            std::cout << "\t\t" << position << " is HUNGRY\n";
        } // exit output critical region

        /*
         * test if philosopher can eat
         * and release the semaphore if allowed
         */
        try_to_eat(position);
    } // exit test critical region

    /*
     * block if philosopher cannot eat yet
     * (waiting for neighbor to release permission).
     *
     * block occurs outside the critical region
     * to avoid deadlocks.
     */
    both_chopsticks_available[position].acquire();
}

/*
 * eat for a random period of time
 */
void eat(size_t position)
{
    size_t duration_in_ms = get_random_value_between(400, 800);

    { // enter critical region
        std::lock_guard<std::mutex> guard(output_mtx);
        std::cout << "\t\t\t\t" << position << " is EATING " << duration_in_ms << "ms\n";
    } // exit critical region

    std::this_thread::sleep_for(std::chrono::milliseconds(duration_in_ms));
}

/*
 * finish eating putting the chopsticks down
 * and check if neighbors can eat.
 *
 * (also here is the point where blocked
 * semaphores can be unlocked in case
 * the neighbor matches a blocked philosopher)
 */
void put_chopsticks(size_t position)
{ // enter critical region
    std::lock_guard<std::mutex> guard(critical_region_mtx);

    state[position] = State::THINKING; // starts thinking

    try_to_eat(left(position)); // see if left neighbor can eat now
    try_to_eat(right(position)); // see if right neighbor can eat now
} // exit critical region

void philosopher(size_t position)
{
    while (true) 
    {
        think(position);
        take_chopsticks(position);
        eat(position);
        put_chopsticks(position);
    }
}

int main(void)
{
    std::jthread ph1 ([&] { philosopher(0); });
    std::jthread ph2 ([&] { philosopher(1); });
    std::jthread ph3 ([&] { philosopher(2); });
    std::jthread ph4 ([&] { philosopher(3); });
    std::jthread ph5 ([&] { philosopher(4); });

    return 0;
}

