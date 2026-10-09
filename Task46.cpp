#include <iostream>
#include <thread>
#include <shared_mutex>
#include <mutex>
#include <chrono>
using namespace std;

int shared_data = 0;
shared_mutex rw_lock;
mutex print_mtx;   

void reader(int id) {
    shared_lock<shared_mutex> lock(rw_lock);
    int v = shared_data;
    lock_guard<mutex> p(print_mtx);
    cout << "Reader " << id << " read value : " << v << endl;
}

void writer(int id, int val) {
    unique_lock<shared_mutex> lock(rw_lock);
    shared_data = val;
    lock_guard<mutex> p(print_mtx);
    cout << "Writer " << id << " updated value to : " << shared_data << endl;
}

int main() {
    auto gap = [] { this_thread::sleep_for(chrono::milliseconds(100)); };
    thread w1(writer, 1, 42);                      w1.join(); gap();
    thread r1(reader, 1), r2(reader, 2);           r1.join(); r2.join(); gap();
    thread w2(writer, 2, 99);                      w2.join(); gap();
    thread r3(reader, 3);                          r3.join();
    return 0;
}
