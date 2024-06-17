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