#include <chrono>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>

class Memory {
private:
    const static size_t LIMIT = 4096; // 4kb

public:
    static size_t used;

    static bool allocate(size_t amount)
    {
        if ((amount + used) > Memory::LIMIT)
            return false;

        used += amount;

        std::cout << "MEMORY USED: " << used << " / " << LIMIT;

        return true;
    }

    static bool deallocate(size_t amount)
    {
        if (amount > used)
            return false;

        used -= amount;

        std::cout << "MEMORY USED: " << used << " / " << LIMIT;

        return true;
    }
};

size_t Memory::used = 0;

enum class PState { NEW, READY, EXECUTING, BLOCKED, FINISHED, REJECTED };
enum class PSchedulerAlgo { SJF, FIFO };

size_t get_random_value(const size_t& min = 300, const size_t& max = 800) {
    static std::mt19937 rnd(std::time(nullptr));

    if (min < max)
        return std::uniform_int_distribution<>(300, 800)(rnd);

    return std::uniform_int_distribution<>(min, max)(rnd);
}

// function to randomly decide whether
// the process will have an I/O block or not
bool should_block_process() {
    static std::mt19937 rnd(std::time(nullptr));
    return std::uniform_int_distribution<>(0, 1)(rnd);
}

// Process sync controls
std::mutex ready_mtx;
std::condition_variable ready_queue_empty_cv;

std::mutex blocked_mtx;
std::condition_variable blocked_queue_empty_cv;

class Process {
private:
    size_t pid;
    PState state;
    std::string name;
    size_t execution_duration_in_ms;
    size_t memory_usage;

    static size_t last_pid;
    static PSchedulerAlgo scheduler_algorithm;

    Process(const std::string &name)
        : pid(++last_pid), name(name), state(PState::NEW),
        execution_duration_in_ms(get_random_value(800, 2000)),
        memory_usage(get_random_value(100, 1000)) {}

public:
    static std::deque<Process *> ready_queue;
    static std::deque<Process *> blocked_queue;
    static std::unordered_map<size_t, Process *> process_table;

    static void create(const std::string &name) {
        Process *p = new Process(name);
        process_table[p->get_pid()] = p;

        size_t duration_to_be_ready = get_random_value();
        p->display_process_information();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(duration_to_be_ready));

        if (!Memory::allocate(p->memory_usage)) {
            std::cout << "I'm sorry, your process is REJECTED\n";
            p->update_state(PState::REJECTED);
        }

        p->update_state(PState::READY);
        p->display_process_information();

        {
            std::lock_guard<std::mutex> guard(ready_mtx);
            ready_queue.push_back(p);
        }

        ready_queue_empty_cv.notify_one();
    }

    size_t get_pid() { return this->pid; }
    PState get_state() { return this->state; }
    std::string get_name() { return this->name; }
    size_t get_execution_duration_in_ms() {
        return this->execution_duration_in_ms;
    }

    std::string get_state_string() {
        switch (this->state) {
            case PState::NEW: return "New";
            case PState::READY: return "Ready";
            case PState::BLOCKED: return "Blocked";
            case PState::FINISHED: return "Finished";
            case PState::EXECUTING: return "Executing";
            case PState::REJECTED: return "Rejected";
            default: return "Corrupted";
        }
    }

    static std::string get_scheduler_algo_string() {
        switch (scheduler_algorithm) {
            case PSchedulerAlgo::SJF: return "SJF";
            case PSchedulerAlgo::FIFO: return "FIFO";
            default: return "None";
        }
    }

    void run() {
        this->update_state(PState::EXECUTING);
        this->display_process_information();

        if (should_block_process()) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(this->execution_duration_in_ms / 2));
            this->update_state(PState::BLOCKED);
            this->display_process_information();

            {
                std::lock_guard<std::mutex> lock(blocked_mtx);
                blocked_queue.push_back(this);
            }
            blocked_queue_empty_cv.notify_one();
            return;
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(this->execution_duration_in_ms));

        if (!Memory::deallocate(this->memory_usage)) {
            std::cout << "Not deallocated\n\n";
        }

        this->update_state(PState::FINISHED);
        this->display_process_information();
    }

    void display_process_information() {
        std::cout << "Process (" << this->get_pid() << ") " << this->get_name()
            << " [" << this->get_state_string() << "]";

        if (this->get_state() == PState::FINISHED)
            std::cout << " | " << this->get_execution_duration_in_ms() << "ms";

        std::cout << "\n";
    }

    void update_state(const PState& new_state) { this->state = new_state; }

    static void list_all_processes() {
        for (auto &[pid, proc] : Process::process_table) {
            std::cout << "\nPID " << pid << ": " << proc->get_name() << " ["
                << proc->get_state_string() << "]\n";
        }
    }

    static void destroy_all() {
        for (auto &[pid, proc] : process_table) {
            delete proc;
        }

        process_table.clear();
    }

    static void switch_scheduler_algo() {
        if (scheduler_algorithm == PSchedulerAlgo::FIFO)
            scheduler_algorithm = PSchedulerAlgo::SJF;
        else
            scheduler_algorithm = PSchedulerAlgo::FIFO;
    }

    static Process* find_shortest_job_from_ready() {
        if (ready_queue.empty()) return nullptr;

        auto shortest_iterator = ready_queue.begin();

        for (auto iterator_ptr = ready_queue.begin(); iterator_ptr != ready_queue.end(); ++iterator_ptr) {
            if ((*iterator_ptr)->execution_duration_in_ms
                < (*shortest_iterator)->execution_duration_in_ms) {
                shortest_iterator = iterator_ptr;
            }
        }

        Process* shortest_job = *shortest_iterator;
        ready_queue.erase(shortest_iterator); // remove from queue
        return shortest_job;
    }
    
    static void scheduler_routine() {
        while (true) {
            std::unique_lock<std::mutex> lock(ready_mtx);

            // wait until queue is not empty
            ready_queue_empty_cv.wait(lock, [] { return !ready_queue.empty(); });

            Process *next = nullptr;

            if (scheduler_algorithm == PSchedulerAlgo::FIFO)
            {
                next = ready_queue.front();
                ready_queue.pop_front();
            }
            else
            {
                next = find_shortest_job_from_ready();
            }

            lock.unlock();

            if (next)
                next->run();
        }
    }

    static void io_device_routine() {
        while (true) {
            std::unique_lock<std::mutex> lock(blocked_mtx);

            // wait until queue is not empty
            blocked_queue_empty_cv.wait(lock, [] { return !blocked_queue.empty(); });

            Process *blocked_p = blocked_queue.front();
            blocked_queue.pop_front();

            lock.unlock();

            std::this_thread::sleep_for(
                std::chrono::milliseconds(get_random_value())
            );

            blocked_p->update_state(PState::READY);
            blocked_p->display_process_information();

            {
                std::lock_guard<std::mutex> ready_lock(ready_mtx);
                ready_queue.push_back(blocked_p);
            }

            ready_queue_empty_cv.notify_one();
        }
    }
};

// initializing static member of Process
size_t Process::last_pid = 0;
PSchedulerAlgo Process::scheduler_algorithm = PSchedulerAlgo::FIFO;
std::deque<Process *> Process::ready_queue;
std::deque<Process *> Process::blocked_queue;
std::unordered_map<size_t, Process *> Process::process_table;

int main(void) {
    // Process threads
    std::jthread scheduler_thread([&] { Process::scheduler_routine(); });
    std::jthread io_device_thread([&] { Process::io_device_routine(); });

    size_t menu_choice;

    std::cout << "[ --- Welcome to Unnamed OS --- ] \n\n";

    while (true) {
        std::cout << "0: Exit\n";
        std::cout << "1: Spawn process\n";
        std::cout << "2: Switch scheduler algorithm (current: "
            << Process::get_scheduler_algo_string() << ")\n";
        std::cout << "3: List all processes\n";
        std::cout << "Choose an option: ";
        std::cin >> menu_choice;

        if (menu_choice == 0)
        {
            Process::destroy_all();
            break;
        }

        if (menu_choice == 1)
        {
            std::string process_name;
            std::cout << "Process name: ";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, process_name);

            Process::create(process_name);
        }

        if (menu_choice == 2)
            Process::switch_scheduler_algo();

        if (menu_choice == 3)
            Process::list_all_processes();
    }

    return 0;
}
