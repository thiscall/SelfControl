#include "showlicence.h"
#include "ui_showlicence.h"

ShowLicence::ShowLicence(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowLicence)
{
    ui->setupUi(this);
}

ShowLicence::~ShowLicence()
{
    delete ui;
}
