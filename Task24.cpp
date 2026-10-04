#include<iostream>
#include<windows.h>
int main(){
STARTUPINFOA si{};
PROCESS_INFORMATION pi{};
si.cb=sizeof(si);
char command[]="cmd.exe /C exit 42";
if (CreateProcessA(nullptr, command, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)){
WaitForSingleObject(pi.hProcess, INFINITE);
DWORD exitCode=0;
GetExitCodeProcess(pi.hProcess , &exitCode);
std::cout<<"Child process exited with code:"<<exitCode<<"\n";
CloseHandle(pi.hThread);
CloseHandle(pi.hProcess); }
 return 0; }
