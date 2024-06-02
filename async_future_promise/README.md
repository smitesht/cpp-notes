In the modern C++, **async**, **future** and **promise** are used for asynchronous programming, enabling concurrent operations and parallelism.

# std::async

std::async is a function template that runs a function asynchronously (potentially in a separate thread) and returns a std::future object that holds the result of the function.

```cpp
#include <iostream>
#include <thread>
#include <future>
#include <chrono>

// function that need to run async

int LongTask(int num)
{
    long sum = 0;
    for(int i=0; i < num; i++){
        std::cout<<"from LongTask "<<i<<std::endl;
        sum = sum + i;
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }

    return sum;
}

int main()
{
    // call LongTask asynchronously
    std::async(LongTask,20);

    return 0;
}

OUTPUT
===================
from LongTask 0
from LongTask 1
from LongTask 2
from LongTask 3
from LongTask 4
from LongTask 5
from LongTask 6
from LongTask 7
from LongTask 8
from LongTask 9
```

In this program std::async runs the LongTask asynchronously.

### How to get the return value from the asynchronous function i.e. LongTask.

# std::future

std::future is a class template that provides a mechanism to access the result of an asynchronous peration. A std::future object is created by std::async, std::promise or other asynchronous providers.

```cpp
int LongTask(int num)
{
    long sum = 0;

    for(int i=0; i < num; i++){
        std::cout<<"from LongTask "<<i<<std::endl;
        sum = sum + i;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return sum;
}

int main()
{
    // call LongTask asynchronously and get the future object
    std::future<int> result = std::async(LongTask, 10);

    // get return value
    int value = result.get();

    std::cout<<"The sum is "<<value<<std::endl;

    return 0;
}
```

# std::promise

std::promise is a class template that provides a way to store a value or an exception to be retrieved by a std::future object. It is used to set the result of an asynchronous operation.

```cpp
void LongTaskWithPromise(std::promise<int> prom, int num)
{
    try
    {
        long sum = 0;

        for(int i=0; i < num; i++){
            std::cout<<"from LongTask "<<i<<std::endl;
            sum = sum + i;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        prom.set_value(sum);
    }
    catch(const std::exception& e)
    {
        prom.set_exception(std::current_exception());
    }

}

int main()
{
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread t1(LongTaskWithPromise, std::move(prom), 12);
    int value = fut.get();

    std::cout<<"The sum is "<<value<<std::endl;
    t1.join();
    return 0;
}

OUTPUT
====================
from LongTask 0
from LongTask 1
from LongTask 2
from LongTask 3
from LongTask 4
from LongTask 5
from LongTask 6
from LongTask 7
from LongTask 8
from LongTask 9
from LongTask 10
from LongTask 11
The sum is 66

```

# std::thread vs std::async

## std::thread

std::thread is a single thread of execution within a program. It allows to create a new thread and run a function in that thread.

- Control and Management

  **std::thread**: provides more control over thread creation, execution and synchronization but requires explicit management.

  **std::async**: Provides automatic management of asynchronous tasks and returns a std::future for accessing results.

- Execution Policies:

  **std::thread**: Always creates a new thread.

  **std::async**: Can create a new thread (std::launch::async) or defer execution until needed (std::launch::deferred)

- Synchromization

  **std::thread**: Requires manual synchronization using mutex, condition variable etc.

  **std::async**: Symplify synchronization by returning a std::future that can be used to retrieve results and handle execptions.

- Resource Management

  **std::thread**: Requires explicit joining or detaching of threads to avoid resource leaks or program termination.

  **std::async**: Manage thread resource automatically, joining threads when the future is destroyed.

- Exception Handling

  **std::thread**: Exception thrown in a thread must be handled within the thread or communicated back to the main thread using mechanisms like std::promize and std::future.

  **std::async**: Exception thrown in the asynchronous task are automatically propagated to the associated std::future and can be retrieved using future.get().
