#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DlgAbout.h"
#include "hppframe.h"

int _ComboBoxforMaster::Row() { return row; }
int _ComboBoxforMaster::Column() { return column; }
void _ComboBoxforMaster::setPosition(int R, int C) { row = R, column = C; }

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i <= 5; i ++ ) ui->master->insertColumn(i);
    ui->master->setHorizontalHeaderLabels(_qs1);

    ui->master->resizeColumnToContents(0);
    ui->master->setColumnWidth(1, 60);
    ui->master->setColumnWidth(2, 60);
    ui->master->setColumnWidth(3, 200);
    ui->master->setColumnWidth(4, 75);
    ui->master->setColumnWidth(5, 120);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAbout_triggered()
{
    about tmp;
    tmp.exec();
}


void MainWindow::on_addDT_clicked()
{
    const int N = ui->master->rowCount();
    ui->master->insertRow(N);

    QCheckBox *ck = new QCheckBox; ck->setChecked(1);
    _ComboBoxforMaster *cb1 = new _ComboBoxforMaster; cb1->addItems(_qs2);
    QComboBox *cb2 = new QComboBox; cb2->addItems(_qs3); cb2->setEnabled(0);
    _ComboBoxforMaster *cb4 = new _ComboBoxforMaster; cb4->addItems(_qs4);
    QComboBox *cb5 = new QComboBox;

    ui->master->setCellWidget(N, 0, ck);
    ui->master->setCellWidget(N, 1, cb1);
    ui->master->setCellWidget(N, 2, cb2);
    ui->master->setCellWidget(N, 4, cb4);
    ui->master->setCellWidget(N, 5, cb5);
    QTableWidgetItem *it1 = new QTableWidgetItem;
    it1->setFlags(it1->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
    ui->master->setItem(N, 3, it1);
}


void MainWindow::on_delDT_clicked()
{
    ui->master->removeRow(ui->master->currentRow());
}


void MainWindow::on_master_cellEntered(int row, int column)
{
    qDebug()<<row<<' '<<column;
}

void sigUpdateExcel(int row, int column) {

}

void MainWindow::on_schStart_clicked()
{
    qDebug()<<"Start task schedule";
    ui->schStart->setEnabled(0);
    ui->schStop->setEnabled(1);
}


void MainWindow::on_schStop_clicked()
{
    qDebug()<<"End task schedule";
    ui->schStop->setEnabled(0);
    ui->schStart->setEnabled(1);
}

