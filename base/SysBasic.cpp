#include "../hppframe.h"
#include <stdio.h>
#include <string.h>
#include <string>

//Global Varibles
LPWSTR _errReason = NULL;
HMODULE hNtdll = NULL;
//zNtShutdown = NULL;
//zNtRaiseHardError = NULL;

//Basic functions

void RaisePsError(LPCWSTR errApi, DWORD errCode, bool fatal)
{
    static wchar_t tmp[4096], msg[1024];
    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errCode, LANG_USER_DEFAULT, msg, 1024, NULL);
    wsprintf(tmp, L"错误位置：%s\n错误函数：%s\n错误代码：%u\n错误信息：%s\n", _errReason, errApi, errCode, msg);
    MessageBoxW(NULL, tmp, L"自律小助手", MB_ICONERROR | MB_TASKMODAL | MB_SETFOREGROUND | MB_TOPMOST);
    if (fatal) ExitProcess(1);
}

extern "C" BOOL EnablePrivilege(LPCWSTR lpszPrivilege)
{
    HANDLE hToken = NULL;
    OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken);
    TOKEN_PRIVILEGES tp;
    LUID luid;

    if ( !LookupPrivilegeValueW(NULL, lpszPrivilege, &luid ) ) {
        RaisePsError(L"LookupPrivilegeValue", GetLastError(), 1);
        return FALSE;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    if ( !AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL) )
    {
          RaisePsError(L"AdjustTokenPrivileges", GetLastError(), 1);
          return FALSE;
    }

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
    {
          RaisePsError(L"AdjustTokenPrivilege", ERROR_NOT_ALL_ASSIGNED, 1);
          return FALSE;
    }
    return TRUE;
}

extern "C" void ReduceWorkingSet() {
    SetProcessWorkingSetSize(GetCurrentProcess(), -1, -1);
}

void InitMain() {
    SetReason(L"申请关机权限");
    EnablePrivilege(SE_SHUTDOWN_NAME);
    SetReason(L"加载 ntdll.dll");
    hNtdll = GetModuleHandleA("ntdll.dll");
    if (!hNtdll) RaisePsError(L"GetModuleHandleA", GetLastError(), 1);
}

BOOL CmpTime(LPSYSTEMTIME _a, LPSYSTEMTIME _b) {
    if (_a->wYear != _b->wYear) return _a->wYear > _b->wYear;
    if (_a->wMonth != _b->wMonth) return _a->wMonth > _b->wMonth;
    if (_a->wDay != _b->wDay) return _a->wDay > _b->wDay;
    if (_a->wHour != _b->wHour) return _a->wHour > _b->wHour;
    if (_a->wMinute != _b->wMinute) return _a->wMinute > _b->wMinute;
    if (_a->wSecond != _b->wSecond) return _a->wSecond > _b->wSecond;
    return 1;
}

void SqConvertA(LPSTR &dst, const QString &src) {
    std::string s = src.toStdString();
    dst = new char[s.size() + 2];
    strcpy(dst, s.data());
}

BOOL SqFilter(LPCSTR src, LPCSTR tl, BYTE flt) {
    BOOL flag;
    if (!flt) return !stricmp(src, tl);
    else {
        for (DWORD i = 0; src[i]; i ++ ) {
            flag = 1;
            for (DWORD j = 0; src[i + j] && tl[j]; j ++ ) if (tolower(src[i + j]) != tolower(tl[j])) flag = 0;
            if (flag) return 1;
        }
    }
    return 0;
}
