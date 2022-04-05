#include "../hppframe.h"
#include <tlhelp32.h>
#include <QDebug>

void EwxPowerAction(DWORD flag)
{
    DWORD res;
    res = ExitWindowsEx(EWX_FORCEIFHUNG | EWX_FORCE | flag, 0);
    if (!res) RaisePsError(L"ExitWindowsEx", GetLastError(), 0);
}

BOOL KillProcessByID(DWORD pid) {
    HANDLE hPs = OpenProcess(PROCESS_TERMINATE, 0, pid);
    if (!hPs) { RaisePsError(L"OpenProcess", GetLastError(), 0); return 0; }
    TerminateProcess(hPs, 1);
    CloseHandle(hPs);
    return 1;
}

#undef PROCESSENTRY32
#undef Process32First
#undef Process32Next
DWORD KillProcessByName(LPKTASK tsk, BOOL bKill) {
    HANDLE hSs = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (!hSs) { RaisePsError(L"CreateToolhelp32Snapshot", GetLastError(), 1); return 0; }
    PROCESSENTRY32 pe = {0};
    pe.dwSize = sizeof(pe);
    if (!Process32First(hSs, &pe)) {
        RaisePsError(L"Process32First", GetLastError(), 0);
        CloseHandle(hSs);
        return 0;
    }
    DWORD res = 0;
    do {
        if (SqFilter(pe.szExeFile, tsk->obj, tsk->flt)) {
            res = 1;
            if (bKill) KillProcessByID(pe.th32ProcessID);
        }
    } while (Process32Next(hSs, &pe));
    CloseHandle(hSs);
    return res;
}

void ExecuteReaction(LPKTASK tsk, DWORD infoLow) {
    switch (tsk->exec)
    {
    case 0: //Kill Process
        switch (tsk->det) {
        case 0: KillProcessByID(infoLow); break;
        case 1: KillProcessByName(tsk, 1); break;
        case 2: RaisePsError(L"ExecuteReaction", ERROR_NOT_SUPPORTED, 0); break; //等待填坑
        }
        break;
    case 1: //Suspend Process
        RaisePsError(L"ExecuteReaction", ERROR_NOT_SUPPORTED, 0); //等待填坑
        break;
    case 2: //Close Window
        RaisePsError(L"ExecuteReaction", ERROR_NOT_SUPPORTED, 0); //等待填坑
        break;
    case 3: //Power off
        if (tsk->det) NULL; //等待填坑
        else EwxPowerAction(EWX_SHUTDOWN);
        break;
    case 4: //Reboot
        if (tsk->det) NULL; //等待填坑
        else EwxPowerAction(EWX_REBOOT);
        break;
    case 5: //BugCheck
        RaisePsError(L"ExecuteReaction", ERROR_NOT_SUPPORTED, 0); //等待填坑
        break;
    }
}

void WINAPI ExecuteSchTasks(LPKVTASKS tsk) {
    SetReason(L"执行计划任务");
    for (auto it : tsk->v) {
        switch (it->tp) {
        case 0: //Any
            ExecuteReaction(it, 0);
            break;
        case 1: //Scan Process
            RaisePsError(L"ExecuteSchTasks", ERROR_NOT_SUPPORTED, 0);
            break;
        case 2: //Scan Windows
            RaisePsError(L"ExecuteSchTasks", ERROR_NOT_SUPPORTED, 0);
            break;
        }
        delete it;
    }
    tsk->v.clear();
}
