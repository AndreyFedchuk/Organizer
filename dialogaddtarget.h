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
    explicit dialogAddTarget(QWidget *parent = 0);
    ~dialogAddTarget();

private:
    Ui::dialogAddTarget *ui;
};

#endif // DIALOGADDTARGET_H
