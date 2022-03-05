#include <iostream>
#include <chrono>
#include <thread>

#include <signal.h>

#include "context.hpp"

Context global_context;

void LongJob(const Context context)
{
    std::cout << "Enter main loop" << std::endl;
    while (!context.IsDone())
    {
        std::cout << "Do short job" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "Leave main loop" << std::endl;
}

void SetupCancellation(const Context context)
{
    struct sigaction action;

    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = [](int signum) -> void
    {
        global_context.Done();
    };

    sigaction(SIGINT, &action, NULL);
}

int main()
{
    global_context = Context();
    SetupCancellation(global_context);

    LongJob(global_context);
    return 0;
}
