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

    void setTarget(const QString str);
    void setDescription(const QString str);
    void setPriority(const int priority);
    void setDeadline(const QDate date);


private:
    Ui::dialogAddTarget *ui;
};

#endif // DIALOGADDTARGET_H
