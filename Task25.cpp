#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
std::mutex m1, m2;
void threadA(){
m1.lock();
std::cout<<"Thread A locked Mutex1,waiting for Mutex 2...\n";
std::this_thread::sleep_for(std::chrono::milliseconds(50));
m2.lock();
m2.unlock();
m1.unlock();
 }
void threadB(){
m2.lock();
std::cout<<"Thread B locked Mutex2, waiting for Mutex 1...\n";
std::this_thread::sleep_for(std::chrono::milliseconds(50));
m1.lock();
m1.unlock();
m2.unlock();
}
int main(){
std::thread t1(threadA);
std::thread t2(threadB);
t1.join();
t2.join();
return 0; }