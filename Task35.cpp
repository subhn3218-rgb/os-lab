#include<iostream>
#include<thread>
#include<vector>
thread_local int localVal=0;
void run(int offset){
localVal += offset;
std::cout<<"ThreadID:"<< std::this_thread::get_id()<<"|localVal=" <<localVal <<"\n";
 }
 int main(){
std::thread t1(run,10);
std::thread t2(run,20);
std::thread t3(run,30);

t1.join();
t2.join();
t3.join();
return 0;}