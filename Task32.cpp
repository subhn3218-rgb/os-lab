#include<iostream>
#include<windows.h>
#include<tlhelp32.h>
int main(){
HANDLE snap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
if(snap==INVALID_HANDLE_VALUE)return 1;
PROCESSENTRY32 pe{};
pe.dwSize=sizeof(PROCESSENTRY32);
int count=0;
if(Process32First(snap, &pe)) {
do{
std::cout<<"PID:"<< pe.th32ProcessID<<"\t"<<pe.szExeFile<<"\n";
count++;
if(count>=5) break; 
 } while(Process32Next(snap,&pe));}
CloseHandle(snap);
return 0;
}