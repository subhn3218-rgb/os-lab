#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "child") {
        cout << "Child PID : " << GetCurrentProcessId() << " terminating now" << endl;
        return 0;
    }
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    string cmd = string("\"") + path + "\" child";
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (!CreateProcessA(NULL, &cmd[0], NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) return 1;

    cout << "Parent sleeping for 10 s without cleaning up. Child is finished but its handle is still open." << endl;
    Sleep(10000);
    DWORD code;
    GetExitCodeProcess(pi.hProcess, &code);
    cout << "Child exit code still readable by parent (zombie-like): " << code << endl;
    CloseHandle(pi.hProcess);   // equivalent of reaping with wait()
    CloseHandle(pi.hThread);
    cout << "Parent cleaned up child . Exiting ." << endl;
    return 0;
}
