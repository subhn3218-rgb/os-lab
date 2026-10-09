
#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "child") {
        cout << "Child Process : PID = " << GetCurrentProcessId()
             << " , Parent PID = " << argv[2] << endl;
        return 0;
    }
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    string cmd = string("\"") + path + "\" child " + to_string(GetCurrentProcessId());

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (!CreateProcessA(NULL, &cmd[0], NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        cout << "Process creation failed" << endl;
        return 1;
    }
    cout << "Parent Process : PID = " << GetCurrentProcessId()
         << " , Created Child PID = " << pi.dwProcessId << endl;
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess); CloseHandle(pi.hThread);
    return 0;
}
