#include <iostream>
#include <thread>
using namespace std;

volatile int counter = 0;   // volatile stops the compiler from collapsing the loop

void increment_task() {
    for (int i = 1; i <= 1000000; i++) counter = counter + 1;
}

int main() {
    thread t1(increment_task), t2(increment_task);
    t1.join(); t2.join();
    cout << "Expected : 2000000 | Actual counter : " << counter << endl;
    return 0;
}
