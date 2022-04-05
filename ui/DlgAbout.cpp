#include "DlgAbout.h"
#include "ui_DlgAbout.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);

    ui->dlgLb3->setText("<a href = \"https://github.com/thiscall/SelfControl\">github.com/thiscall/SelfControl</a>");
    ui->dlgLb3->setOpenExternalLinks(1);
}

about::~about()
{
    delete ui;
}
