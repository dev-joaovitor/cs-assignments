#include <chrono>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>

enum class PState { NEW, READY, EXECUTING, BLOCKED, FINISHED };

size_t get_random_value() {
    size_t min = 300, max = 800;

    static std::mt19937 rnd(std::time(nullptr));
    return std::uniform_int_distribution<>(min, max)(rnd);
}

// function to randomly decide if
// the process will have an I/O block
bool should_block_process() {
    static std::mt19937 rnd(std::time(nullptr));
    return std::uniform_int_distribution<>(0, 1)(rnd);
}

// sync controls
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

    static size_t last_pid;

    Process(const std::string &name)
        : pid(++last_pid), name(name), state(PState::NEW),
        execution_duration_in_ms(get_random_value()) {}

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
        p->update_state(PState::READY);
        p->display_process_information();

        {
            std::lock_guard<std::mutex> guard(ready_mtx);
            ready_queue.push_back(p);
        }

        ready_queue_empty_cv.notify_one();
    }

    // getters
    size_t get_pid() { return this->pid; }
    PState get_state() { return this->state; }
    std::string get_name() { return this->name; }
    size_t get_execution_duration_in_ms() {
        return this->execution_duration_in_ms;
    }

    std::string getStateString() {
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

        this->update_state(PState::FINISHED);
        this->display_process_information();
    }

    void display_process_information() {
        std::cout << "Process (" << this->get_pid() << ") " << this->get_name()
            << " [" << this->getStateString() << "]";

        if (this->get_state() == PState::FINISHED)
            std::cout << " | " << this->get_execution_duration_in_ms() << "ms";

        std::cout << "\n";
    }

    void update_state(const PState& new_state) { this->state = new_state; }

    static void list_all_processes() {
        for (auto &[pid, proc] : Process::process_table) {
            std::cout << "\nPID " << pid << ": " << proc->get_name() << " ["
                << proc->getStateString() << "]\n";
        }
    }

    static void destroy_all() {
        for (auto &[pid, proc] : process_table) {
            delete proc;
        }

        process_table.clear();
    }

    static void scheduler_routine() {
        while (true) {
            std::unique_lock<std::mutex> lock(ready_mtx);

            // wait until queue is not empty
            ready_queue_empty_cv.wait(lock, [] { return !ready_queue.empty(); });

            Process *next = ready_queue.front();
            ready_queue.pop_front();

            lock.unlock();

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
                std::chrono::milliseconds(get_random_value()));

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
std::deque<Process *> Process::ready_queue;
std::deque<Process *> Process::blocked_queue;
std::unordered_map<size_t, Process *> Process::process_table;

int main(void) {
    // Process threads
    std::jthread scheduler_thread([&] { Process::scheduler_routine(); });
    std::jthread io_device_thread([&] { Process::io_device_routine(); });

    size_t menu_choice;

    while (true) {
        std::cout << "--- Welcome to Unnamed OS ---\n";
        std::cout << "0: Exit\n";
        std::cout << "1: Spawn process\n";
        std::cout << "2: List all processes\n";
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
            Process::list_all_processes();
    }

    return 0;
}
