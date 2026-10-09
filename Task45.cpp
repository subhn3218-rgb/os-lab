#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

queue<int> buffer;
const size_t CAPACITY = 3;
mutex mtx;
condition_variable cv_producer, cv_consumer;

void producer() {
    for (int item = 1; item <= 5; item++) {
        unique_lock<mutex> lock(mtx);
        while (buffer.size() == CAPACITY) cv_producer.wait(lock);
        buffer.push(item);
        cout << "Produced : " << item << endl;
        cv_consumer.notify_one();
    }
}

void consumer() {
    for (int i = 1; i <= 5; i++) {
        unique_lock<mutex> lock(mtx);
        while (buffer.empty()) cv_consumer.wait(lock);
        int item = buffer.front(); buffer.pop();
        cout << "Consumed : " << item << endl;
        cv_producer.notify_one();
    }
}

int main() {
    thread p(producer), c(consumer);
    p.join(); c.join();
    return 0;
}
