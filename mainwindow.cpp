#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tgTableModel * model = new tgTableModel(this);
    ui->tableView->setModel(model);

    tgPriorityDelegate * delegate = new tgPriorityDelegate(this);
    ui->tableView->setItemDelegateForColumn((int)Column::Priority, delegate);


//    ui->tableView->setColumnWidth((int)Column::Name, /*250*/200);
//    ui->tableView->resizeRowToContents((int)Column::Name);
//    ui->tableView->setColumnWidth((int)Column::Description, 150);
//    ui->tableView->resizeColumnToContents((int)Column::Deadline);
//    ui->tableView->resizeColumnToContents((int)Column::Priority);


}

MainWindow::~MainWindow()
{
    delete ui;
}
