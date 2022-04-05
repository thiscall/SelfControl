#ifndef SHOWLICENCE_H
#define SHOWLICENCE_H

#include <QDialog>

namespace Ui {
class ShowLicence;
}

class ShowLicence : public QDialog
{
    Q_OBJECT

public:
    explicit ShowLicence(QWidget *parent = nullptr);
    ~ShowLicence();

private:
    Ui::ShowLicence *ui;
};

#endif // SHOWLICENCE_H
