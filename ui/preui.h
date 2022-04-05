#ifndef PREUI_H
#define PREUI_H

#include <QMainWindow>

namespace Ui {
class PreUI;
}

class PreUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit PreUI(QWidget *parent = nullptr);
    ~PreUI();

private slots:
    void on_actionabout_triggered();

    void on_actionDebug_triggered();

    void on_btStop_clicked();

    void on_btRun_clicked();

    void on_actionLicence_triggered();

private:
    Ui::PreUI *ui;
};

#endif // PREUI_H
