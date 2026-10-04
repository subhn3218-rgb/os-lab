#include<iostream>
#include<thread>
#include<vector>
#include<windows.h>
HANDLE startEvent;
void worker(int id){
 WaitForSingleObject(startEvent,INFINITE);
 std::cout<<"Worker "<< id <<" triggered!\n";
 }
int main(){
 startEvent=CreateEventA(nullptr,TRUE,FALSE,nullptr);
  std::vector<std::thread>workers;
 for(int i= 1;i<=3;++i){
workers.emplace_back(worker,i);
}
std::cout<<"Waiting1secondbeforebroadcastingstartsignal...\n";
Sleep(1000);
 SetEvent(startEvent);
for(auto& t: workers) {
t.join();
}
 CloseHandle(startEvent);
  return 0;
   }