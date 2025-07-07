// processes

#include <chrono>
#include <condition_variable>
#include <ctime>
#include <deque>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <thread>


enum class PState
{
    NEW, READY, EXECUTING,
    BLOCKED, FINISHED
};

size_t get_random_value()
{
    size_t min = 300,
        max = 800;

    static std::mt19937 rnd(std::time(nullptr));
    return std::uniform_int_distribution<>(min, max)(rnd);
}

bool should_block_process()
{
    static std::mt19937 rnd(std::time(nullptr));
    return std::uniform_int_distribution<>(0, 1)(rnd);
}

std::mutex ready_mtx;
std::condition_variable ready_queue_empty_cv;

std::mutex blocked_mtx;
std::condition_variable blocked_queue_empty_cv;

class Process
{
private:
    size_t pid;
    PState state;
    std::string name;
    size_t execution_duration_in_ms;

    static unsigned int last_pid;

public:
    static std::deque<Process*> ready_queue;
    static std::deque<Process*> blocked_queue;

    Process(std::string name)
        : pid(++last_pid), name(name), state(PState::NEW),
        execution_duration_in_ms(get_random_value())
    {
        size_t duration_to_be_ready = get_random_value();
        this->displayProcessInformation();

        std::this_thread::sleep_for(std::chrono::milliseconds(duration_to_be_ready));
        this->updateState(PState::READY);
        this->displayProcessInformation();

        {
            std::lock_guard<std::mutex> guard(ready_mtx);
            ready_queue.push_back(this);
        }

        ready_queue_empty_cv.notify_one();
    }

    // getters
    size_t getPID() { return this->pid; }
    PState getState() { return this->state; }
    std::string getName() { return this->name; }
    size_t getExecutionDurationInMs() { return this->execution_duration_in_ms; }

    std::string getStateString()
    {
        switch (this->state) {
            case PState::NEW:
                return "New";
            case PState::READY:
                return "Ready";
            case PState::EXECUTING:
                return "Executing";
            case PState::BLOCKED:
                return "Blocked";
            case PState::FINISHED:
                return "Finished";
            default:
                return "Corrupted";
        }
    }

    // actions
    void run()
    {
        this->updateState(PState::EXECUTING);
        this->displayProcessInformation();

        if (should_block_process())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(this->execution_duration_in_ms / 2));
            this->updateState(PState::BLOCKED);
            this->displayProcessInformation();

            {
                std::lock_guard<std::mutex> lock(blocked_mtx);
                blocked_queue.push_back(this);
            }
            blocked_queue_empty_cv.notify_one();
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(this->execution_duration_in_ms));

        this->updateState(PState::FINISHED);
        this->displayProcessInformation();
    }

    void displayProcessInformation()
    {
        std::cout << "Process (" << this->getPID() << ") "
            << this->getName() << " [" << this->getStateString()
            << "] | " << this->getExecutionDurationInMs() << "ms" << "\n";
    }

    static void scheduler_routine()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock(ready_mtx);

            // wait until queue is not empty
            ready_queue_empty_cv.wait(lock, [] { return !ready_queue.empty(); });

            Process* next = ready_queue.front();
            ready_queue.pop_front();

            lock.unlock();

            next->run();
        }
    }

    static void io_device_routine()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock(blocked_mtx);

            // wait until queue is not empty
            blocked_queue_empty_cv.wait(lock, [] { return !blocked_queue.empty(); });

            Process* blocked_p = blocked_queue.front();
            blocked_queue.pop_front();

            lock.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(get_random_value()));

            blocked_p->updateState(PState::READY);
            blocked_p->displayProcessInformation();

            {
                std::lock_guard<std::mutex> ready_lock(ready_mtx);
                ready_queue.push_back(blocked_p);
            }

            ready_queue_empty_cv.notify_one();
        }
    }

    // setters
    void updateState (PState new_state) { this->state = new_state; }
};

// initializing static member of Process
unsigned int Process::last_pid = 0;
std::deque<Process*> Process::ready_queue;
std::deque<Process*> Process::blocked_queue;

int main (void)
{
    std::jthread scheduler_thread ([&] { Process::scheduler_routine(); });
    std::jthread io_device_thread ([&] { Process::io_device_routine(); });

    Process p("First");
    Process p2("Second");
    Process p3("Third");
    Process p4("Fourth");

    return 0;
}

