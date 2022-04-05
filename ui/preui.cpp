#include "preui.h"
#include "ui_preui.h"
#include "dlgabout.h"
#include "mainwindow.h"
#include "showlicence.h"
#include "../hppframe.h"
#include <string>

PreUI::PreUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PreUI)
{
    ui->setupUi(this);
    SYSTEMTIME tm;
    GetLocalTime(&tm);
    ui->nHour->setValue(tm.wHour);
    ui->nMinute->setValue(tm.wMinute);
}

PreUI::~PreUI()
{
    delete ui;
}

void PreUI::on_actionabout_triggered()
{
    about dlg;
    dlg.exec();
}

DWORD WINAPI AuthorMode(LPVOID unused) {
    QApplication a(__argc, __argv);
    MainWindow w;
    w.show();
    return a.exec();
}

void PreUI::on_actionDebug_triggered()
{
    CloseHandle(CreateThread(NULL, 0, AuthorMode, NULL, 0, NULL));
}


void PreUI::on_btStop_clicked()
{
    if (StopSchTasks()) {
        ui->btRun->setEnabled(1);
        ui->btStop->setEnabled(0);
    }
    DeleteSchTasks();
}


void PreUI::on_btRun_clicked()
{
    LPKTASK tsk = new KTASK;
    tsk->flt = 1;
    if (ui->chPwrOff->isChecked()) tsk->exec = 3;
    else if (ui->chReboot->isChecked()) tsk->exec = 4;
    else {
        tsk->exec = 0, tsk->det = 1;
        SqConvertA(tsk->obj, ui->stPsName->text());
    }
    LPKVTASKS v = new KVTASKS;
    v->v.push_back(tsk);
    GetLocalTime(&v->sch);
    v->sch.wHour = ui->nHour->value();
    v->sch.wMinute = ui->nMinute->value();
    v->sch.wSecond = 0;
    NewTaskSchedule(v);
    if (RunSchTasks()) {
        ui->btRun->setEnabled(0);
        ui->btStop->setEnabled(1);
    }
}


void PreUI::on_actionLicence_triggered()
{
    ShowLicence w;
    w.exec();
}

