#include <process.h>
#include <iostream>
using namespace std;

int main() {
    cout << "Child replacing its binary with 'cmd /c dir' ..." << endl;
    cout.flush();
    const char* args[] = { "cmd", "/c", "dir", NULL };
    int rc = _spawnvp(_P_WAIT, "cmd", args);
    if (rc == -1) cout << "exec failed" << endl;
    cout << "Parent reaped replaced child image" << endl;
    return 0;
}
