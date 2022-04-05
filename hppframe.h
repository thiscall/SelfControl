#ifndef HPPFRAME_H
#define HPPFRAME_H

#include <QStringList>
#include <vector>
#include <windows.h>

extern LPWSTR _errReason;
#define SetReason(x) _errReason = x

//Structure Definitions

class _KTASK {
public:
    BYTE tp, exec, det;
    BYTE flt;
    LPSTR obj;
    _KTASK() : obj(NULL), tp(0), exec(0), det(0), flt(0) { }
    ~_KTASK() { if (obj) delete [] obj; }
};

typedef _KTASK KTASK, *LPKTASK;

typedef struct _KVTASKS {
    std::vector<KTASK*> v;
    SYSTEMTIME sch;
}KVTASKS, *LPKVTASKS;

//Constant Definitions

const QStringList _qs1 = QStringList() << "启用" << "检测" << "符合模式" << "对象" << "响应" << "执行方式";
const QStringList _qs2 = QStringList() << "任意" << "进程名" << "窗口标题";
const QStringList _qs3 = QStringList() << "等于" << "包含";
const QStringList _qs4 = QStringList() << "终止进程" << "挂起进程" << "关闭窗口" << "关机" << "重启" << "强制蓝屏";
const QStringList _qs5 = QStringList() << "终止该进程" << "终止全部同名进程" << "结束进程树";
const QStringList _qs6 = QStringList() << "正常关机（ExitWindowsEx）" << "强制关机（NtShutdownSystem）";

//undocumented functions

typedef LONG (WINAPI *_ZFPROC1)(INT);
//_ZFPROC1 zNtShutdownSystem = NULL;
typedef LONG (WINAPI *_ZFPROC2)();
//_ZFPROC2 zNtRaiseHardError = NULL; //0xC000000C STATUS_TIMER_NOT_CANCELED

//基础函数

void RaisePsError(LPCWSTR errPos, DWORD errCode, bool fatal);
extern "C" BOOL EnablePrivilege(LPCWSTR lpszPrivilege);
extern "C" void ReduceWorkingSet();
void InitMain();
BOOL CmpTime(LPSYSTEMTIME _a, LPSYSTEMTIME _b);
void SqConvertA(LPSTR &dst, const QString &src);
BOOL SqFilter(LPCSTR src, LPCSTR tl, BYTE flt);

//任务管理函数

BOOL RunSchTasks();
BOOL StopSchTasks();
BOOL DeleteSchTasks();
BOOL NewTaskSchedule(LPKVTASKS pt);

//动作执行函数

void EwxPowerAction(DWORD flag);
BOOL KillProcessByID(DWORD pid);
DWORD KillProcessByName(LPKTASK tsk, bool bKill);
void ExecuteSchTasks(LPKVTASKS tsk); //没写完

#endif // HPPFRAME_H
