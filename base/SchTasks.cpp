#include "../hppframe.h"

HANDLE _hKhex;
std::vector<LPKVTASKS> _Khv;
DWORD _KhStatus = 0;

DWORD WINAPI KhRunner(LPVOID unused) {
    SYSTEMTIME dt;
    while (1) {
        GetLocalTime(&dt);
        for (auto it : _Khv) {
            if (CmpTime(&dt, &it->sch)) ExecuteSchTasks(it);
        }
        Sleep(5000);
    }
}

BOOL RunSchTasks() {
    if (_KhStatus) { RaisePsError(L"RunSchTasks", ERROR_LOCKED, 0); return 0; }
    _hKhex = CreateThread(NULL, 0, KhRunner, NULL, 0, NULL);
    if (!_hKhex) { RaisePsError(L"CreateThread", GetLastError(), 0); return 0; }
    _KhStatus = 1;
    return 1;
}

BOOL StopSchTasks() {
    if (!_KhStatus) { RaisePsError(L"StopSchTasks", ERROR_HANDLE_EOF, 0); return 0; }
    TerminateThread(_hKhex, 0);
    CloseHandle(_hKhex);
    _hKhex = NULL;
    _KhStatus = 0;
    return 1;
}

BOOL DeleteSchTasks() {
    if (_KhStatus) { RaisePsError(L"DeleteSchTasks", ERROR_LOCKED, 0); return 0; }
    for (auto it : _Khv) delete it;
    _Khv.clear();
    return 1;
}

BOOL NewTaskSchedule(LPKVTASKS pt) {
    if (_KhStatus) { RaisePsError(L"CreateTaskSchedule", ERROR_LOCKED, 0); return 0; }
    _Khv.push_back(pt);
    return 1;
}
