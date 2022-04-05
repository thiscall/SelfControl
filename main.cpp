#include "ui/preui.h"
#include "ui/mainwindow.h"
#include "hppframe.h"

int main(int argc, char *argv[])
{
    SYSTEMTIME tm_end, tm;
    tm_end.wYear = 2022, tm_end.wMonth = 5, tm_end.wDay = 1;
    GetLocalTime(&tm);
    if (CmpTime(&tm, &tm_end)) {
        MessageBoxW(NULL, L"该预发布版本已过期。\n请前往 github.com/thiscall/SelfControl 下载最新版本。", L"自律小助手", MB_ICONERROR);
    }
    QApplication a(argc, argv);
    PreUI w;
    w.show();
    InitMain();
    ReduceWorkingSet();
    return a.exec();
}
