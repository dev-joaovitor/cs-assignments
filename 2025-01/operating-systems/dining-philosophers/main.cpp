#include <iostream>
#include <chrono>
#include <random>
#include <semaphore>
#include <mutex>
#include <thread>

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
}

/*
 * position of the right neighbor of i-th philosopher
 */
size_t inline right(size_t i)
{
    return (i + 1) % N_OF_PHILOSOPHERS;
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
std::binary_semaphore both_forks_available[N_OF_PHILOSOPHERS]
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

void think(size_t position)
{
    size_t duration_in_ms = get_random_value_between(400, 800);

    { // critical region
        std::lock_guard<std::mutex> guard(output_mtx);
        std::cout << position << " is thinking " << duration_in_ms << "ms\n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(duration_in_ms));
}

void philosopher(size_t position)
{
    while (true) 
    {
        think(position);
        //take_forks(position);
        //eat(position);
        //put_forks(position);
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
