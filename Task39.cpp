#include <windows.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

bool processAlive(DWORD pid) {
    HANDLE h = OpenProcess(SYNCHRONIZE, FALSE, pid);
    if (!h) return false;
    bool alive = WaitForSingleObject(h, 0) == WAIT_TIMEOUT;
    CloseHandle(h);
    return alive;
}

int main(int argc, char* argv[]) {
    if (argc > 2 && string(argv[1]) == "child") {
        DWORD ppid = (DWORD)atoi(argv[2]);
        cout << "Initial Parent PID : " << ppid << endl;
        Sleep(3000);
        cout << "After parent dies , recorded Parent PID : " << ppid
             << (processAlive(ppid) ? " (parent still alive)" : " (parent is gone - orphan)") << endl;
        cout << "Press Enter to close..."; cin.get();
        return 0;
    }
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    string cmd = string("\"") + path + "\" child " + to_string(GetCurrentProcessId());
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (!CreateProcessA(NULL, &cmd[0], NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) return 1;
    cout << "Parent PID : " << GetCurrentProcessId() << " exiting immediately" << endl;
    CloseHandle(pi.hProcess); CloseHandle(pi.hThread);
    return 0;  
}
