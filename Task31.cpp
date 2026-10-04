#include<iostream>
#include<windows.h>
int main(){
char* page=(char*)VirtualAlloc(nullptr,4096,
MEM_COMMIT,PAGE_READWRITE);
page[0]='A';
DWORD oldProtect;
VirtualProtect(page,4096,PAGE_READONLY,&oldProtect);
__try{
page[0]='B';
}
__except(EXCEPTION_EXECUTE_HANDLER){
std::cout<<"Hardware memory protection trap caught!\n";
 }
 VirtualFree(page, 0,MEM_RELEASE);
 return 0;
 }