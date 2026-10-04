#include<iostream>
#include<future>
#include<chrono>
#include<thread>
int main(){
std::future<double>task =std::async(std::launch::async,[](){
std::this_thread::sleep_for(std::chrono::seconds(1));
return 3.14159; });
std::cout<<"Main thread continues work while a sync task computes...\n";
double result=task.get();
std::cout<<"Resultreceived:"<<result<<"\n";
return 0;}