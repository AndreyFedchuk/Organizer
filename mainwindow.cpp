#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pTableModel = new tgTableModel(this);
    ui->tableView->setModel(m_pTableModel);


    tgPriorityDelegate * delegate = new tgPriorityDelegate(this);
    ui->tableView->setItemDelegateForColumn((int)Column::Priority, delegate);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setColumnWidth((int)Column::Name, /*250*/200);
    ui->tableView->resizeRowToContents((int)Column::Name);
    ui->tableView->setColumnWidth((int)Column::Description, 150);
    ui->tableView->resizeColumnToContents((int)Column::Deadline);
    ui->tableView->resizeColumnToContents((int)Column::Priority);


    connect(ui->m_pbtnAdd, SIGNAL(clicked()), m_pTableModel, SLOT(slotAddRow()));
    connect(ui->m_pbtbDel, SIGNAL(clicked()), this, SLOT(slotDeleteButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotDeleteButton()
{
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    if(index.isValid())
        m_pTableModel->slotDelRow(index);
}
