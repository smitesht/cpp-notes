# Producer Consumer Problem

This code allowes producer to produce an item and allowed consumer to consume.

After producing an item it norify the consumer and wait for the consumption.

After consuming an item, it notify the producer to produce item.

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <queue>

using namespace std;

// shared variable
queue<int> bucket;
mutex mtxBucket;
condition_variable cv;

// after every single produce or consume notify other
bool isproduced = false;

// The producer first lock the shared resource
// wait at conditional variable for producing.
// if allowed to produce, add item to queue
// reset produced flag and notify the consumer to consume single item
void threadProducer() {

    int count = 0;
    while (count < 10) {
        std::unique_lock<mutex> lock(mtxBucket);
        cv.wait(lock, [] {
            return !isproduced; });
        bucket.push(count);
        cout << "Produced "<<count<<" ..." << endl;
        count++;
        isproduced = true;
        cv.notify_one();

    }

}

// The consumer first lock the shared resource
// wait for the consume an item
// if alloed consume item and reset produced flag
// notify to the producer to produce an item
void threadConsumer() {


    while (true) {
        unique_lock<mutex> lock(mtxBucket);
        cv.wait(lock, [] {
            return isproduced; });
        int count = bucket.front();
        cout << "Consumed "<<count <<" ..." << endl;
        bucket.pop();
        isproduced = false;
        cv.notify_one();
        std::this_thread::sleep_for(chrono::seconds(1));
        if (count >= 9)
            break;
    }
}

int main()
{
    thread t1(threadProducer);
    thread t2(threadConsumer);

    t1.join();
    t2.join();
}
```

OUTPUT

```cpp
Produced 0 ...
Consumed 0 ...
Produced 1 ...
Consumed 1 ...
Produced 2 ...
Consumed 2 ...
Produced 3 ...
Consumed 3 ...
Produced 4 ...
Consumed 4 ...
Produced 5 ...
Consumed 5 ...
Produced 6 ...
Consumed 6 ...
Produced 7 ...
Consumed 7 ...
Produced 8 ...
Consumed 8 ...
Produced 9 ...
Consumed 9 ...

```
