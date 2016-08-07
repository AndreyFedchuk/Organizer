#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QSettings>
#include "tgtablemodel.h"
#include "tgprioritydelegate.h"
#include "tgstatusdelegate.h"
#include "dialogaddtarget.h"
#include "setproxyparam.h"
#include "dailytasksmodel.h"
#include "dialogdailytask.h"
#include "dsetting.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    tgTableModel * m_pTargetModel;
    QSortFilterProxyModel * m_pProxyTarget;
    DailyTasksModel * m_pTaskModel;
    QSortFilterProxyModel * m_pProxyTask;
    QString m_lastLoadPath;
    QString m_dataTG;
    QString m_nameStyle;
    QSettings m_settings;


    bool targetFromDialog(dialogAddTarget * pDialog);
    void changeRangeProgBar(int val);
    void syncCompletedParam();
    void btnEnabled(bool enable);
    void readSettings();
    void writeSettings();

private slots:
    void slotDeleteButton();
    void slotAddButton();
    void slotEditButton();
    void slotChangeLCD(int val);
    void slotLoad();
    void slotSaveAs();

    void on_tableView_clicked(const QModelIndex &index);
    void on_m_pCheckBoxFilter_toggled(bool checked);
    void slotEditFilter();
    void on_calendarWidget_TS_clicked(const QDate &date);
    void on_m_pbtnAdd_TS_clicked();
    void on_m_pbtnEdit_TS_clicked();
    void on_m_pbtnDel_TS_clicked();
    void on_actionSetting_triggered();
};

#endif // MAINWINDOW_H
