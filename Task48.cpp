#include <windows.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "child") {
        char buffer[128] = {0};
        DWORD n = 0;
        ReadFile(GetStdHandle(STD_INPUT_HANDLE), buffer, sizeof(buffer) - 1, &n, NULL);
        buffer[n] = '\0';
        cout << "Child read from pipe : " << buffer << endl;
        return 0;
    }
    SECURITY_ATTRIBUTES sa = { sizeof(sa), NULL, TRUE };   // inheritable handles
    HANDLE rd, wr;
    CreatePipe(&rd, &wr, &sa, 0);
    SetHandleInformation(wr, HANDLE_FLAG_INHERIT, 0);      // child must not inherit write end

    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    string cmd = string("\"") + path + "\" child";
    STARTUPINFOA si = { sizeof(si) };
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = rd;
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    PROCESS_INFORMATION pi;
    if (!CreateProcessA(NULL, &cmd[0], NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) return 1;
    CloseHandle(rd);                                       // parent closes read end

    const char* msg = "Hello Child from Kernel Pipe";
    DWORD written;
    WriteFile(wr, msg, (DWORD)strlen(msg), &written, NULL);
    CloseHandle(wr);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess); CloseHandle(pi.hThread);
    return 0;
}
