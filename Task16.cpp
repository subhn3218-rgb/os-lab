#include<iostream>
#include<thread>
#include<vector>
 #include<windows.h>
HANDLE sem;
 void worker(int id){
 WaitForSingleObject(sem,INFINITE);
std::cout<<"Thread"<<id <<" acquiredresource.\n";
Sleep(1000);
std::cout<<"Thread"<<id <<"releasing resource.\n";
 ReleaseSemaphore(sem, 1, nullptr);
 }
 int main(){
  sem=CreateSemaphoreA(nullptr, 2, 2,nullptr);
std::vector<std::thread>threads;
for(int i= 1;i<=4;++i){
threads.emplace_back(worker, i);
 }
for(auto& t: threads) {
t.join();
}
 CloseHandle(sem);
 return 0;
 }
