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
