#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include "tgtablemodel.h"
#include "tgprioritydelegate.h"
#include "tgstatusdelegate.h"
#include "dialogaddtarget.h"
#include "setproxyparam.h"

#include <QDebug> //to test

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    tgTableModel * m_pTableModel;
    QSortFilterProxyModel * m_pProxyModel;

    bool targetFromDialog(dialogAddTarget * pDialog);
    void changeRangeProgBar(int val);
    void syncCompletedParam();

private slots:
    void slotDeleteButton();
    void slotAddButton();
    void slotEditButton();
    void slotChangeLCD(int val);
    void slotLoad();
    void slotSave();

    void on_tableView_clicked(const QModelIndex &index);
    void on_m_pCheckBoxFilter_toggled(bool checked);
    void slotEditFilter();
};

#endif // MAINWINDOW_H
