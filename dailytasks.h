#ifndef DAILYTASKS_H
#define DAILYTASKS_H

#include <QDialog>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include "dailytasksmodel.h"
#include "dialogdailytask.h"

namespace Ui {
class DailyTasks;
}

class DailyTasks : public QDialog
{
    Q_OBJECT

public:
    explicit DailyTasks(QWidget *parent = nullptr);
    ~DailyTasks();

private slots:
    void on_calendarWidget_clicked(const QDate &date);
    void on_m_pbtnAdd_clicked();
    void on_m_pbtnEdit_clicked();
    void on_m_pbtnDel_clicked();

private:
    Ui::DailyTasks *ui;
    DailyTasksModel * m_pTaskModel;
    QSortFilterProxyModel * m_pProxy;
};

#endif // DAILYTASKS_H
