// ///////////////////////////////////////////////////
// Copyright © 2016 Andriy Hudz. All rights reserved.
// email: andrey.hudz.90@gmail.com
// https://www.facebook.com/AndreyHudz90
// ///////////////////////////////////////////////////

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
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
    QString m_nameStyle;
    QSettings m_settings;
    QTranslator * m_pTranslator;

    void changeRangeProgBar(int val);
    void syncCompletedParam();
    void readSettings();
    void writeSettings();
    void changeTranslator(QString postfix);

private slots:
    void slotDeleteButton();
    void slotAddButton();
    void slotEditButton();
    void slotChangeLCD(int val);

    void on_tableView_clicked(const QModelIndex &index);
    void on_m_pCheckBoxFilter_toggled(bool checked);
    void slotEditFilter();
    void on_calendarWidget_TS_clicked(const QDate &date);
    void on_m_pbtnAdd_TS_clicked();
    void on_m_pbtnEdit_TS_clicked();
    void on_m_pbtnDel_TS_clicked();
    void on_actionSetting_triggered();
    void on_actionAbout_organizer_triggered();
    void on_tabWidget_currentChanged(int index);
    void on_actionEnglish_triggered();
    void on_actionRussian_triggered();
    void on_actionUkrainian_triggered();
};

#endif // MAINWINDOW_H
