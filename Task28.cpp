#include<iostream>
#include<windows.h>
int main(){
HANDLE hFile=CreateFileA("guard_test.txt",
GENERIC_READ|GENERIC_WRITE,
FILE_SHARE_READ |FILE_SHARE_WRITE,
nullptr,CREATE_ALWAYS, 0,nullptr);
if(hFile==INVALID_HANDLE_VALUE)return 1;
 if(LockFile(hFile,0,0,100,0)){
std::cout<<"Byterange[0-100]lockedsuccessfully.\n";
UnlockFile(hFile, 0,0,100,0);
std::cout<<"Byterangeunlocked.\n";
 }
CloseHandle(hFile);
return 0;
}