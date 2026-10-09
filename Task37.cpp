
#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "child") {
        cout << "Child executing task ..." << endl;
        Sleep(2000);
        cout << "Child exiting with code 42" << endl;
        return 42;
    }
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    string cmd = string("\"") + path + "\" child";
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (!CreateProcessA(NULL, &cmd[0], NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        cout << "Process creation failed" << endl;
        return 1;
    }
    cout << "Parent waiting for child ..." << endl;
    WaitForSingleObject(pi.hProcess, INFINITE);   // wait()
    DWORD code = 0;
    GetExitCodeProcess(pi.hProcess, &code);
    cout << "Parent : Child terminated with exit status " << code << endl;
    CloseHandle(pi.hProcess); CloseHandle(pi.hThread);
    return 0;
}
