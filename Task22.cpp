#include<iostream>
#include<windows.h>
int main(){
void* base=VirtualAlloc(nullptr,1024 * 1024,
MEM_RESERVE, PAGE_NOACCESS);
if( !base) return 1;
std::cout<<"Reserved 1 MB address space at:" <<base<<"\n";
int* page=(int*)VirtualAlloc(base, 4096, MEM_COMMIT, PAGE_READWRITE);
if(!page) return 1;
page[0]=42;
std::cout<<"Committed memory value:"<<page[0]<<"\n";
VirtualFree(base, 0, MEM_RELEASE);
return 0;
}