#include<iostream>
#include<thread>
#include<windows.h>
void pinnedWorker(){
DWORD_PTR mask=1;
DWORD_PTR prev=SetThreadAffinityMask(GetCurrentThread(), mask);
if(prev!=0) {
std::cout<<"Thread successfully bound to Core0.\n"; }}
int main(){
std::cout<<"Available hardware cores:"
<<std::thread::hardware_concurrency() <<"\n";
std::thread t(pinnedWorker);
t.join();
 return 0;
}
