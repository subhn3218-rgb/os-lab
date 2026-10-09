#include <windows.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const char* SHM_NAME = "Local\\shm_os_lab";

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "child") {
        Sleep(1000);
        HANDLE h = OpenFileMappingA(FILE_MAP_READ, FALSE, SHM_NAME);
        if (!h) { cout << "Child could not open shared memory" << endl; return 1; }
        char* ptr = (char*)MapViewOfFile(h, FILE_MAP_READ, 0, 0, 1024);
        cout << "Child read from SHM : " << ptr << endl;
        UnmapViewOfFile(ptr); CloseHandle(h);
        return 0;
    }
    HANDLE h = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1024, SHM_NAME);
    char* ptr = (char*)MapViewOfFile(h, FILE_MAP_ALL_ACCESS, 0, 0, 1024);

    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    string cmd = string("\"") + path + "\" child";
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (!CreateProcessA(NULL, &cmd[0], NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) return 1;

    strcpy(ptr, "OS Shared Memory Payload");
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess); CloseHandle(pi.hThread);
    UnmapViewOfFile(ptr); CloseHandle(h);  
    return 0;
}
