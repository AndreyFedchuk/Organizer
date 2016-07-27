#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "tgtablemodel.h"
#include "tgprioritydelegate.h"
#include "tgstatusdelegate.h"
#include "dialogaddtarget.h"

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

    bool targetFromDialog(dialogAddTarget * pDialog);

private slots:
    void slotDeleteButton();
    void slotAddButton();
    void slotEditButton();

    void on_tableView_clicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
