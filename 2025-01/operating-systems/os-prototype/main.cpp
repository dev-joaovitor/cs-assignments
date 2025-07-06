// processes

#include <deque>
#include <iostream>
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

class Process
{
private:
    size_t pid;
    PState state;
    std::string name;
    size_t duration_in_ms;

    static unsigned int last_pid;

public:
    static std::deque<Process> ready_queue;
    static std::deque<Process> blocked_queue;

    Process(std::string name)
        : pid(++last_pid), name(name), state(PState::NEW),
        duration_in_ms(get_random_value())
    {
    }

    // getters
    size_t getPID() { return this->pid; }
    PState getState() { return this->state; }
    std::string getName() { return this->name; }
    size_t getDurationInMs() { return this->duration_in_ms; }

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

    // setters
    void updateState (PState new_state) { this->state = new_state; }
};

// initializing static member of Process
unsigned int Process::last_pid = 0;
std::deque<Process> Process::ready_queue;
std::deque<Process> Process::blocked_queue;

int main (void)
{
    Process p("Angus");

    std::cout << "Process: " << p.getPID() << "\n"
        << p.getName() << "\n" << p.getStateString()
        << "\n" << p.getDurationInMs() << "ms" << "\n";

    p.updateState(PState::FINISHED);

    std::cout << "Process: " << p.getPID() << "\n"
        << p.getName() << "\n" << p.getStateString()
        << "\n" << p.getDurationInMs() << "ms" << "\n";


    return 0;
}

