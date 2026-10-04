#include<iostream>
#include<windows.h>
int main(){
HANDLE hFile=CreateFileA("async.bin", GENERIC_WRITE,0,nullptr,
CREATE_ALWAYS, FILE_FLAG_OVERLAPPED,nullptr);
if(hFile==INVALID_HANDLE_VALUE)return 1;
OVERLAPPED ol{};
ol.hEvent=CreateEventA(nullptr,TRUE, FALSE, nullptr);
 char buffer[1024]="Asynchronous file write data packet.";
WriteFile(hFile, buffer, sizeof(buffer),nullptr,&ol);
std::cout<<"I/O initiated.Doing computation in parallel...\n";
 WaitForSingleObject(ol.hEvent,INFINITE);
std::cout<<"Asynchronous writefully committed.\n";
 CloseHandle(ol.hEvent);
 CloseHandle(hFile);
return 0;
}
