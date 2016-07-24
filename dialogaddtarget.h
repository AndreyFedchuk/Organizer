#ifndef DIALOGADDTARGET_H
#define DIALOGADDTARGET_H

#include <QDialog>

namespace Ui {
class dialogAddTarget;
}

class dialogAddTarget : public QDialog
{
    Q_OBJECT

public:
    explicit dialogAddTarget(QWidget *parent = nullptr);
    ~dialogAddTarget();

    QString Target();
    QString Description();
    int Priority();
    QDate Deadline();


private:
    Ui::dialogAddTarget *ui;
};

#endif // DIALOGADDTARGET_H
