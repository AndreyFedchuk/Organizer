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

    ui->tableView->setColumnWidth((int)Column::Name, 200);
    ui->tableView->resizeRowToContents((int)Column::Name);
    ui->tableView->setColumnWidth((int)Column::Description, 150);
    ui->tableView->resizeColumnToContents((int)Column::Deadline);
    ui->tableView->resizeColumnToContents((int)Column::Priority);


    connect(ui->m_pbtnAdd, SIGNAL(clicked()), SLOT(slotAddButton()));
    connect(ui->m_pbtbDel, SIGNAL(clicked()), SLOT(slotDeleteButton()));
    connect(ui->m_pbtnEdit, SIGNAL(clicked(bool)), SLOT(slotEditButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::targetFromDialog(dialogAddTarget *pDialog)
{
    if(pDialog->exec() == QDialog::Accepted)
    {
        target tg;
        tg.name = pDialog->Target();
        tg.description = pDialog->Description();
        tg.priority = pDialog->Priority();
        tg.deadline = pDialog->Deadline();
        tg.ready = false;

        m_pTableModel->AddRow(tg);
        return true;
    }
    else
        return false;
}

void MainWindow::slotDeleteButton()
{
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    index = index.sibling(index.row(), static_cast<int>(Column::Name));
    QVariant var = m_pTableModel->data(index, Qt::DisplayRole);
    target targetName;
    targetName.name = var.toString();

    if(index.isValid())
    {
        QMessageBox * pMes =  new QMessageBox(QMessageBox::Warning, "Delete the target",
                                             "Want to remove the target: \"<b>" + targetName.name + "</b>\" ?",
                                             QMessageBox::Yes | QMessageBox::No,
                                             this);

        if(pMes->exec() == QMessageBox::Yes)
        {
            m_pTableModel->DelRow(index);
        }
    }
}

void MainWindow::slotAddButton()
{
    dialogAddTarget * pAddDialog = new dialogAddTarget;
    targetFromDialog(pAddDialog);
    delete pAddDialog;
}

void MainWindow::slotEditButton()
{
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    target tg = m_pTableModel->EditRow(index);
    dialogAddTarget * pDialog = new dialogAddTarget;
    pDialog->setWindowTitle("Edit target");
    pDialog->setTarget(tg.name);
    pDialog->setDescription(tg.description);
    pDialog->setDeadline(tg.deadline);
    pDialog->setPriority(tg.priority);

    if(targetFromDialog(pDialog))
       m_pTableModel->DelRow(index);
    delete pDialog;
}









