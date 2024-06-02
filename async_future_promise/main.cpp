#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <exception>
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
    // call LongTask asynchronously 
    //std::async(LongTask,20);

    //std::future<int> result = std::async(LongTask, 10);
    //int value = result.get();

    //std::cout<<"The sum is "<<value<<std::endl;

    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread t1(LongTaskWithPromise, std::move(prom), 12);
    int value = fut.get();
    
    std::cout<<"The sum is "<<value<<std::endl;
    t1.join();
    return 0;
}

