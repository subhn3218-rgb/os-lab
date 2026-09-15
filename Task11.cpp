#include<iostream>
#include<thread>
using namespace std;
void worker() {
 std::cout
<< "Worker thread is running\n";
 }
 int main(){
std::thread t(worker);
std::cout<< "Main thread is running\n";
t.join();
return 0;
}