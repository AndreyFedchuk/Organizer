// ///////////////////////////////////////////////////
// Copyright © 2016 Andriy Hudz. All rights reserved.
// email: andrey.hudz.90@gmail.com
// https://www.facebook.com/AndreyHudz90
// ///////////////////////////////////////////////////

#ifndef DIALOGADDTARGET_H
#define DIALOGADDTARGET_H

#include <QDialog>
#include "target.h"

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
    Status::Value getStatus();

    void setTarget(const QString str);
    void setDescription(const QString str);
    void setPriority(const int priority);
    void setDeadline(const QDate date);
    void setStatus(Status::Value val);

private:
    Ui::dialogAddTarget *ui;
};

#endif // DIALOGADDTARGET_H
