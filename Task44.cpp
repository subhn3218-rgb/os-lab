#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int counter = 0;
mutex mtx;

void safe_increment() {
    for (int i = 1; i <= 100000; i++) {
        mtx.lock();
        counter = counter + 1;
        mtx.unlock();
    }
}

int main() {
    thread t1(safe_increment), t2(safe_increment);
    t1.join(); t2.join();
    cout << "Final counter with Mutex : " << counter << endl;
    return 0;
}
