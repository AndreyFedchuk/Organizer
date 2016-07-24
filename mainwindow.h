#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tgtablemodel.h"
#include "tgprioritydelegate.h"
#include "dialogaddtarget.h"

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

private slots:
    void slotDeleteButton(); //for test

    void slotAddButton();
};

#endif // MAINWINDOW_H
