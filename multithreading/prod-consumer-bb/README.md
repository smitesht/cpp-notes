# Producer Consumer Problem With Bounded Buffer

Producer Consumer problem is a classical example of a multithreading problem where proeucer produces data and placing it into a shared buffer, and consumers are taking data from the buffer for processing. When the buffer is full, producer must wait and when the buffer is empty, consumer must wait. The solution contains proper synchronization to ensure thread safety and avoid race conditions.

The code contains one producer and two consumers.

## Global Variables

```cpp

const int BUFFER_SIZE = 3; // Size of the bounded buffer
queue<int> sharedQ; // Bounded buffer
mutex mtxPQ; // mutex for synchronization
condition_variable cv; // for notification
condition_variable cv1; // notify for end
bool isEndOfProduced = false;

```

## Producer Thread

```cpp

// Producer Thread
void threadProducer(int numOfItems)
{
    for (int ind = 1; ind <= numOfItems; ind++)
    {
        // lock the mutex
        unique_lock<mutex> lock(mtxPQ);
        // if the queue size is more than BUFFER_SIZE = 3,
        //  it will wait for consumption
        cv.wait(lock, [] {
            return sharedQ.size() < BUFFER_SIZE;
            });

        // push the item in queue
        int item = 100 + ind ;
        sharedQ.push(item);
        cout << "Produced Item: " << item << endl;

        // unlock mutex and notify to consumer for consumption
        lock.unlock();
        cv.notify_all();

        // this can be removed, used to smoothly see the operations
        this_thread::sleep_for(chrono::seconds(1));
    }

    // this code notify all the consumers to finish of production
    {
        unique_lock<mutex> lock(mtxPQ);
        isEndOfProduced = true;
    }
    // notify to all the consumers
    cv.notify_all();

}

```

## Consumer Thread

```cpp

// consumer thread
void threadConsumer(int id)
{
    while (true)
    {
        // lock the mutex
        unique_lock<mutex> lock(mtxPQ);

        // wait until queue is empty or the isEndOfProduced is false
        cv.wait(lock, [] {
            return !sharedQ.empty() || isEndOfProduced;
            });

        // consume item
        if (!sharedQ.empty())
        {
            int item = sharedQ.front();
            sharedQ.pop();
            cout << "Consumer :" << id << "  consume: " << item << endl;
        }
        else if(isEndOfProduced)
        {
            // if end of production break the loop
            break;
        }

        // unlock and notify that consumed an item
        lock.unlock();
        cv.notify_all();

        // this can be removed, used to smoothly see the operations
        this_thread::sleep_for(chrono::seconds(3));
    }
}

```
