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
    ui->tableView->setItemDelegateForColumn(static_cast<int>(Column::Priority), delegate);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::SelectedClicked
                                     | QAbstractItemView::DoubleClicked);
    ui->tableView->setColumnHidden(static_cast<int>(Column::Description), true);

    QHeaderView * header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeToContents);
    header->setSectionResizeMode(static_cast<int>(Column::Name), QHeaderView::Stretch);
    ui->tableView->resizeRowsToContents();




    connect(ui->m_pbtnAdd, SIGNAL(clicked()), SLOT(slotAddButton()));
    connect(ui->m_pbtbDel, SIGNAL(clicked()), SLOT(slotDeleteButton()));
    connect(ui->m_pbtnEdit, SIGNAL(clicked()), SLOT(slotEditButton()));
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
        tg.ready = pDialog->getStatus();

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
    ui->tableView->resizeRowsToContents();
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
    pDialog->setStatus(tg.ready);

    if(targetFromDialog(pDialog))
    {
       m_pTableModel->DelRow(index);
       ui->tableView->resizeRowsToContents();
    }
    delete pDialog;
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    auto newIndex = index.sibling(index.row(), static_cast<int>(Column::Description));
    if(newIndex.isValid())
    {
        QString strDescr = m_pTableModel->data(newIndex, Qt::DisplayRole).toString();
        ui->m_ptxtDesc->setText(strDescr);
    }
}
