#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

int shared_counter = 100;

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "child") {
        shared_counter = shared_counter + 50;
        cout << "Child sees shared_counter = " << shared_counter << endl;
        return 0;
    }
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    string cmd = string("\"") + path + "\" child";
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (!CreateProcessA(NULL, &cmd[0], NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) return 1;
    WaitForSingleObject(pi.hProcess, INFINITE);
    cout << "Parent sees shared_counter = " << shared_counter << endl;
    CloseHandle(pi.hProcess); CloseHandle(pi.hThread);
    return 0;
}
