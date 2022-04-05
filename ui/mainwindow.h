#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void sigUpdateExcel(int row, int column);

private slots:
    void on_actionAbout_triggered();

    void on_addDT_clicked();

    void on_delDT_clicked();

    void on_master_cellEntered(int row, int column);

    void on_schStart_clicked();

    void on_schStop_clicked();

private:
    Ui::MainWindow *ui;
};

class _ComboBoxforMaster : public QComboBox
{
public:
    int Row();
    int Column();
    void setPosition(int R, int C);
protected:
    int row, column;
};

#endif // MAINWINDOW_H
