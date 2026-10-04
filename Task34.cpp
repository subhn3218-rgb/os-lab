#include<iostream>
#include<thread>
#include<fstream>
#include<windows.h>
void triggerFileAction() {
Sleep(500);
std::ofstream f("trigger.tmp");
f<<"change";
 f.close();
}
int main(){
HANDLE hChange=FindFirstChangeNotificationA(".",FALSE,
FILE_NOTIFY_CHANGE_FILE_NAME|FILE_NOTIFY_CHANGE_LAST_WRITE);
std::cout<<"Watching directory formodifications...\n";
std::thread t(triggerFileAction);
WaitForSingleObject(hChange,INFINITE);
std::cout<<"Directory change detected!\n";
t.join();
FindCloseChangeNotification(hChange);
DeleteFileA("trigger.tmp");
return 0;
}