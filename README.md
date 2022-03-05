# PoC for Cancellation Context in C++

Just likes the the `context` in Golang.

Implemented by `shared_pointer`, support copy and move semantic automatically.

## Use Case

For any daemon or long jobs require cancellation. Inject a context to provide the
possibility to cancel the daemon / job later.

For daemon program, we can initialize a global context variable, and use signal handler
to indicate the cancellation status. The main loop in the daemon can then checks the
status in some cancellation point.

## Example

```cpp
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
```

Expect output

```
$ ./main
Enter main loop
Do short job
Do short job
Do short job
^CLeave main loop <- Trigger interrupt here
```

## Further Readings

- [c++ - Cancelling a thread using pthread_cancel : good practice or bad - Stack Overflow](https://stackoverflow.com/questions/4760687/cancelling-a-thread-using-pthread-cancel-good-practice-or-bad)
