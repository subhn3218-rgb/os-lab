#include<iostream>
#include<thread>
#include<vector>
#include<atomic>
std::atomic<long> counter{0};
void increment(){
for(int i= 0;i<100000;++i){
counter.fetch_add(1, std::memory_order_relaxed); } }
int main(){
std::vector<std::thread>threads;
for(int i= 0;i<4;++i) {
threads.emplace_back(increment);
}
for(auto& t: threads) {
 t.join();
 }
std::cout<<"Final Atomic Counter:"<<counter<< "\n";
return 0; }