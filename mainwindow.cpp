#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tgTableModel * model = new tgTableModel(this);
    ui->tableView->setModel(model);
//    ui->tableView->setColumnWidth(0, 150);
//    ui->tableView->setColumnWidth(1, 200);
//    ui->tableView->setColumnWidth(2, 25);
//    ui->tableView->setColumnWidth(3, 65);

}

MainWindow::~MainWindow()
{
    delete ui;
}
