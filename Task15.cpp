#include<iostream>
#include<windows.h>
using namespace std;
int main(){
	 HANDLE readPipe, writePipe;
	 CreatePipe(
 &readPipe,
 &writePipe,
 nullptr,
 0
);
 const char message[] =
"Hello through the pipe!";
 DWORD written, read;
 char buffer[100] = {};
 WriteFile(
 writePipe,
 message,
 sizeof(message),
 &written,
 nullptr
 );
 ReadFile(
readPipe,
buffer,
sizeof(buffer),
&read,
 nullptr
);
 std::cout << buffer <<"\n";
 CloseHandle(readPipe);
CloseHandle(writePipe);
}