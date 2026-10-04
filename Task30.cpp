#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<chrono>
std::condition_variable cv;
std::mutex m;
bool ready=false;
void consumer(){
std::unique_lock<std::mutex>lock(m);
cv.wait(lock,[]{return ready;});
std::cout<<"Condition met,consumer awakened.\n"; }
void producer(){
std::this_thread::sleep_for(std::chrono::milliseconds(500));
 {
std::lock_guard<std::mutex>lock(m);
ready=true; }
cv.notify_one(); 
}
int main(){
std::thread tCons(consumer);
std::thread tProd(producer);
tCons.join();
tProd.join();
return 0;
 }
