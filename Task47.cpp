#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>
using namespace std;

timed_mutex mutexA, mutexB;
mutex print_mtx;

void say(const char* s) { lock_guard<mutex> p(print_mtx); cout << s << endl; }

void thread1_work() {
    mutexA.lock();
    say("Thread 1 acquired Lock A , waiting for Lock B ...");
    this_thread::sleep_for(chrono::seconds(1));
    if (!mutexB.try_lock_for(chrono::seconds(3))) {
        say("[ Program execution blocked indefinitely in circular wait ]");
        exit(0);
    }
    mutexB.unlock(); mutexA.unlock();
}

void thread2_work() {
    mutexB.lock();
    say("Thread 2 acquired Lock B , waiting for Lock A ...");
    this_thread::sleep_for(chrono::seconds(1));
    if (!mutexA.try_lock_for(chrono::seconds(3))) {
        say("[ Program execution blocked indefinitely in circular wait ]");
        exit(0);
    }
    mutexA.unlock(); mutexB.unlock();
}

int main() {
    thread t1(thread1_work), t2(thread2_work);
    t1.join(); t2.join();
    return 0;
}
