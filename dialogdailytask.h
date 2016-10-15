// ///////////////////////////////////////////////////
// Copyright © 2016 Andriy Hudz. All rights reserved.
// email: andrey.hudz.90@gmail.com
// https://www.facebook.com/AndreyHudz90
// ///////////////////////////////////////////////////

#ifndef DIALOGDAILYTASK_H
#define DIALOGDAILYTASK_H

#include <QDialog>

namespace Ui {
class dialogDailyTask;
}

class dialogDailyTask : public QDialog
{
    Q_OBJECT

public:
    explicit dialogDailyTask(QWidget *parent = 0);
    ~dialogDailyTask();

    quint32 getID();
    void setID(quint32 &id);
    QString getTask();
    void setTask(QString &str);
    QDate getDate();
    void setDate(QDate &date);
    bool getCompleted();
    void setCompleted(bool enable);

private:
    Ui::dialogDailyTask *ui;
};

#endif // DIALOGDAILYTASK_H
