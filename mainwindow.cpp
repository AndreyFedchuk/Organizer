#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //base Param
    ui->setupUi(this);
    m_pTableModel = new tgTableModel(this);
    ui->tableView->setModel(m_pTableModel);
    m_pProxyModel = new QSortFilterProxyModel(this);
    m_pProxyModel->setSourceModel(m_pTableModel);
    m_pProxyModel->setFilterKeyColumn(static_cast<int>(Column::Ready));
    ui->tableView->setSortingEnabled(true);
    m_pProxyModel->sort(static_cast<int>(Column::Priority), Qt::DescendingOrder);
    ui->m_plcdReady->display(m_pTableModel->completedCount());
    ui->m_pprogBarMain->setRange(0, m_pTableModel->rowCount());
    ui->m_pprogBarMain->setValue(ui->m_plcdReady->value());


    //init delegate
    tgPriorityDelegate * delegate = new tgPriorityDelegate(this);
    ui->tableView->setItemDelegateForColumn(static_cast<int>(Column::Priority), delegate);
    tgStatusDelegate * delegateStatus = new tgStatusDelegate(this);
    ui->tableView->setItemDelegateForColumn(static_cast<int>(Column::Ready), delegateStatus);

    //Setting to view
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::SelectedClicked
                                     | QAbstractItemView::DoubleClicked);
    ui->tableView->setColumnHidden(static_cast<int>(Column::Description), true);
    QHeaderView * header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeToContents);
    header->setSectionResizeMode(static_cast<int>(Column::Name), QHeaderView::Stretch);
    ui->tableView->resizeRowsToContents();

    //SLOTs and SIGNALs
    connect(ui->actionEditFilter, SIGNAL(triggered(bool)), SLOT(slotEditFilter()));
    connect(ui->m_pbtnAdd, SIGNAL(clicked()), SLOT(slotAddButton()));
    connect(ui->m_pbtbDel, SIGNAL(clicked()), SLOT(slotDeleteButton()));
    connect(ui->m_pbtnEdit, SIGNAL(clicked()), SLOT(slotEditButton()));
    connect(m_pTableModel, SIGNAL(completedCountChanged(int)), SLOT(slotChangeLCD(int)));
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

        //for LCD
        int plus(1);
        if(tg.ready == Status::Value::completed)
            slotChangeLCD(plus);

        //for ProgressBar
        changeRangeProgBar(1);
        return true;
    }
    else
        return false;
}

void MainWindow::changeRangeProgBar(int val)
{
    ui->m_pprogBarMain->setRange(0, ui->m_pprogBarMain->maximum() + val);
}

void MainWindow::slotDeleteButton()
{
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    if(index.isValid())
    {
        index = index.sibling(index.row(), static_cast<int>(Column::Name));
        QVariant var = m_pTableModel->data(index, Qt::DisplayRole);
        target targetName;
        targetName.name = var.toString();
        QMessageBox * pMes =  new QMessageBox(QMessageBox::Warning, "Delete the target",
                                             "Want to remove the target: \"<b>" + targetName.name + "</b>\" ?",
                                             QMessageBox::Yes | QMessageBox::No,
                                             this);

        if(pMes->exec() == QMessageBox::Yes)
        {
            // for LCD
            int minus(-1);
            index = index.sibling(index.row(), static_cast<int>(Column::Ready));
            var = m_pTableModel->data(index, Qt::DisplayRole);
            targetName.ready = Status::from_string(var.toString());
            if(targetName.ready == Status::Value::completed)
                slotChangeLCD(minus);

            //for ProgressBar
            changeRangeProgBar(-1);

            m_pTableModel->DelRow(index);

        }
    }
    else
        QMessageBox::information(this, "Information", "Select row to delete");
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
    if(index.isValid())
    {        
        target tg = m_pTableModel->EditRow(index);
        dialogAddTarget * pDialog = new dialogAddTarget;
        pDialog->setWindowTitle("Edit target");
        pDialog->setTarget(tg.name);
        pDialog->setDescription(tg.description);
        pDialog->setDeadline(tg.deadline);
        pDialog->setPriority(tg.priority);
        pDialog->setStatus(tg.ready);

        //for LCD
        int minus(-1);
        Status::Value val = tg.ready;

        if(targetFromDialog(pDialog))
        {
            m_pTableModel->DelRow(index);
            ui->tableView->resizeRowsToContents();

            //for LCD
            if(val == Status::Value::completed)
                slotChangeLCD(minus);
        }
        delete pDialog;
    }
    else
        QMessageBox::information(this, "Information", "Select row to edite");
}

void MainWindow::slotChangeLCD(int val)
{
    ui->m_plcdReady->display(ui->m_plcdReady->value() + val);
    ui->m_pprogBarMain->setValue(ui->m_pprogBarMain->value() + val);
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

void MainWindow::on_m_pCheckBoxFilter_toggled(bool checked)
{
    if(checked)
        ui->tableView->setModel(m_pProxyModel);
    else
        ui->tableView->setModel(m_pTableModel);
}

void MainWindow::slotEditFilter()
{
    SetProxyParam * pDialog = new SetProxyParam(this);
    if(pDialog->exec() == QDialog::Accepted)
    {
        QString str = "";
        if(pDialog->inProcess())
            str += "in process";
        if(pDialog->inWaiting())
            str.isEmpty() ? str += "in waiting" : str += "|in waiting";
        if(pDialog->Completed())
            str.isEmpty() ? str += "completed" : str += "|completed";
        if(pDialog->Deferred())
            str.isEmpty() ? str += "deferred" : str += "|deferred";

        m_pProxyModel->setFilterRegExp(str);
    }
    delete pDialog;
}
