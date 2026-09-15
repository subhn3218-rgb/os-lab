#include<iostream>
#include<windows.h>
using namespace std;
int main(){
	HANDLE process = GetCurrentProcess();
if(SetPriorityClass(
 process,
 BELOW_NORMAL_PRIORITY_CLASS)) {
std::cout
<< "Process priority changed successfully.\n";
 }
else{
std::cout
 << "Could not change process priority.\n";
}
}