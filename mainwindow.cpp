#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_settings("ahudz", "Organizer"),
    m_nameStyle("")
{
    //base Param TARGETS
    ui->setupUi(this);
    m_pTargetModel = new tgTableModel(this);
    ui->tableView->setModel(m_pTargetModel);
    m_pProxyTarget = new QSortFilterProxyModel(this);
    m_pProxyTarget->setSourceModel(m_pTargetModel);
    m_pProxyTarget->setFilterKeyColumn(static_cast<int>(Column::Ready));
    ui->tableView->setSortingEnabled(true);
    m_pProxyTarget->sort(static_cast<int>(Column::Priority), Qt::DescendingOrder);
    syncCompletedParam();
    ui->mainToolBar->setVisible(false);
    readSettings();

    //base Param TASKS
    m_pTaskModel = new DailyTasksModel(this);
    m_pProxyTask = new QSortFilterProxyModel(this);
    m_pProxyTask->setSourceModel(m_pTaskModel);
    m_pProxyTask->setFilterKeyColumn(static_cast<int>(taskColumn::Date));
    ui->tableView_TS->setModel(m_pProxyTask);
    ui->tableView_TS->setSortingEnabled(true);
    m_pProxyTask->sort(static_cast<int>(taskColumn::ID));
    ui->progressBar_TS->setRange(0, m_pTaskModel->rowCount());
    ui->progressBar_TS->setValue(m_pTaskModel->getCountCompleted());


    //init delegate TARGETS
    tgPriorityDelegate * delegate = new tgPriorityDelegate(this);
    ui->tableView->setItemDelegateForColumn(static_cast<int>(Column::Priority), delegate);
    tgStatusDelegate * delegateStatus = new tgStatusDelegate(this);
    ui->tableView->setItemDelegateForColumn(static_cast<int>(Column::Ready), delegateStatus);

    //Setting to view TARGETS
    QBrush br;
    br.setTextureImage(QImage(":/image/bg.png"));
    QPalette pal;
    pal.setBrush(QPalette::Base, br);
    ui->m_ptxtDesc->setPalette(pal);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::SelectedClicked
                                     | QAbstractItemView::DoubleClicked);
    ui->tableView->setColumnHidden(static_cast<int>(Column::Description), true);
    QHeaderView * header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeToContents);
    header->setSectionResizeMode(static_cast<int>(Column::Name), QHeaderView::Stretch);
    ui->tableView->resizeRowsToContents();

    //Setting to view TASKS
    ui->tableView_TS->setSelectionBehavior(QAbstractItemView::SelectItems);
    header = ui->tableView_TS->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeToContents);
    header->setSectionResizeMode(static_cast<int>(taskColumn::Task), QHeaderView::Stretch);
    ui->tableView_TS->verticalHeader()->setHidden(true);
    ui->calendarWidget_TS->setSelectedDate(QDate::currentDate());

    //SLOTs and SIGNALs
    connect(ui->actionEditFilter, SIGNAL(triggered(bool)), SLOT(slotEditFilter()));
    connect(ui->m_pbtnAdd, SIGNAL(clicked()), SLOT(slotAddButton()));
    connect(ui->m_pbtbDel, SIGNAL(clicked()), SLOT(slotDeleteButton()));
    connect(ui->m_pbtnEdit, SIGNAL(clicked()), SLOT(slotEditButton()));
    connect(m_pTargetModel, SIGNAL(completedCountChanged(int)), SLOT(slotChangeLCD(int)));
}

MainWindow::~MainWindow()
{
    writeSettings();
    delete m_pTargetModel;
    delete m_pProxyTarget;
    delete m_pTaskModel;
    delete m_pProxyTask;
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

        m_pTargetModel->AddRow(tg);

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

void MainWindow::syncCompletedParam()
{
    ui->m_plcdReady->display(m_pTargetModel->completedCount());
    ui->m_pprogBarMain->setRange(0, m_pTargetModel->rowCount());
    ui->m_pprogBarMain->setValue(ui->m_plcdReady->value());
}

void MainWindow::readSettings()
{
    m_settings.beginGroup("/Settings");
    int curInd = m_settings.value("/TabIndex").toInt();
    QPoint Pos = m_settings.value("/Pos").toPoint();
    m_nameStyle = m_settings.value("/nameStyle").toString();
    m_settings.endGroup();

    ui->tabWidget->setCurrentIndex(curInd);
    this->move(Pos);
    if(!m_nameStyle.isEmpty())
        QApplication::setStyle(m_nameStyle);
}

void MainWindow::writeSettings()
{
    m_settings.beginGroup("/Settings");
    m_settings.setValue("/TabIndex", ui->tabWidget->currentIndex());
    m_settings.setValue("/Pos", pos());
    m_settings.setValue("/nameStyle", m_nameStyle);
    m_settings.endGroup();

}

void MainWindow::slotDeleteButton()
{
    QModelIndex index;
    if(ui->m_pCheckBoxFilter->isChecked())
        index = m_pProxyTarget->mapToSource(ui->tableView->selectionModel()->currentIndex());
    else
        index = ui->tableView->selectionModel()->currentIndex();
    if(index.isValid())
    {
        index = index.sibling(index.row(), static_cast<int>(Column::Name));
        QVariant var = m_pTargetModel->data(index, Qt::DisplayRole);
        target targetName;
        targetName.name = var.toString();
        QMessageBox * pMes =  new QMessageBox(QMessageBox::Warning, "Delete the target",
                                             "Want to remove the target: \"<b>" + targetName.name + "</b>\" ?",
                                             QMessageBox::Yes | QMessageBox::No,
                                             this);

        if(pMes->exec() == QMessageBox::Yes)
        {
            //to LCD
            int minus(-1);
            index = index.sibling(index.row(), static_cast<int>(Column::Ready));
            var = m_pTargetModel->data(index, Qt::DisplayRole);
            targetName.ready = Status::from_string(var.toString());
            if(targetName.ready == Status::Value::completed)
                slotChangeLCD(minus);

            //to ProgressBar
            changeRangeProgBar(-1);

            m_pTargetModel->DelRow(index);
        }
        delete pMes;
    }
    else
        QMessageBox::information(this, "Information", "Select target to delete");
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
    QModelIndex index;
    if(ui->m_pCheckBoxFilter->isChecked())
        index = m_pProxyTarget->mapToSource(ui->tableView->selectionModel()->currentIndex());
    else
        index = ui->tableView->selectionModel()->currentIndex();
    if(index.isValid())
    {        
        target tg = m_pTargetModel->EditRow(index);
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
            m_pTargetModel->DelRow(index);
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
    QModelIndex _index = index;
    if(ui->m_pCheckBoxFilter->isChecked())
        _index = m_pProxyTarget->mapToSource(index);
    auto newIndex = _index.sibling(_index.row(), static_cast<int>(Column::Description));
    if(newIndex.isValid())
    {
        QString strDescr = m_pTargetModel->data(newIndex, Qt::DisplayRole).toString();
        ui->m_ptxtDesc->setText(strDescr);
    }
}

void MainWindow::on_m_pCheckBoxFilter_toggled(bool checked)
{
    if(checked)
        ui->tableView->setModel(m_pProxyTarget);
    else
        ui->tableView->setModel(m_pTargetModel);
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

        m_pProxyTarget->setFilterRegExp(str);
    }
    delete pDialog;
}

void MainWindow::on_calendarWidget_TS_clicked(const QDate &date)
{
    m_pProxyTask->setFilterRegExp(date.toString("yyyy-MM-dd"));
    ui->tableView_TS->setColumnHidden(static_cast<int>(taskColumn::Date), true);
    ui->tableView_TS->resizeRowsToContents();

    //to progressBar
    if(m_pProxyTask->rowCount())
    {
        int nCountCompleted(0);
        QModelIndex index;
        for(int i(0); i < m_pProxyTask->rowCount(); ++i)
        {
            index =  m_pProxyTask->index(i, static_cast<int>(taskColumn::Completed));
            if(index.isValid())
            {
                if(index.data().toString() == "ready")
                    ++nCountCompleted;
            }
            else
                break;
        }
        ui->progressBar_TS->setRange(0, m_pProxyTask->rowCount());
        ui->progressBar_TS->setValue(nCountCompleted);
    }
    else
    {
        ui->progressBar_TS->setRange(0, 1);
        ui->progressBar_TS->setValue(0);
    }
}

void MainWindow::on_m_pbtnAdd_TS_clicked()
{
    dialogDailyTask * pDialog = new dialogDailyTask(this);
    if(pDialog->exec() == QDialog::Accepted)
    {
        task tmp;
        tmp.ID = pDialog->getID();
        tmp.taskName = pDialog->getTask();
        tmp.date = pDialog->getDate();
        tmp.completed = pDialog->getCompleted();
        m_pTaskModel->addTask(tmp);
        ui->tableView_TS->resizeRowsToContents();
    }
    delete pDialog;
}

void MainWindow::on_m_pbtnEdit_TS_clicked()
{
    QModelIndex index = m_pProxyTask->mapToSource(ui->tableView_TS->selectionModel()->currentIndex());
    if(index.isValid())
    {
        task ts = m_pTaskModel->editTask(index);

        dialogDailyTask * pDialog = new dialogDailyTask(this);
        pDialog->setWindowTitle("Edit task");
        pDialog->setID(ts.ID);
        pDialog->setDate(ts.date);
        pDialog->setTask(ts.taskName);
        pDialog->setCompleted(ts.completed);
        if(pDialog->exec() == QDialog::Accepted)
        {
            ts.ID = pDialog->getID();
            ts.taskName = pDialog->getTask();
            ts.date = pDialog->getDate();
            ts.completed = pDialog->getCompleted();
            m_pTaskModel->delTask(index);
            m_pTaskModel->addTask(ts);
            ui->tableView_TS->resizeRowsToContents();
        }
        delete pDialog;
    }
    else
        QMessageBox::information(this, "Information", "Select row to edite");
}

void MainWindow::on_m_pbtnDel_TS_clicked()
{
    QModelIndex index = m_pProxyTask->mapToSource(ui->tableView_TS->selectionModel()->currentIndex());
    if(index.isValid())
    {
        index = index.sibling(index.row(), static_cast<int>(taskColumn::Task));
        QVariant var = m_pTaskModel->data(index);
        QString str = var.toString();
        QMessageBox * msg = new QMessageBox(QMessageBox::Warning, "Delete the task",
                                            "Want to remove the target: \"<b>" + str + "</b>\" ?",
                                            QMessageBox::Yes | QMessageBox::No,
                                            this);
        if(msg->exec() == QMessageBox::Yes)
            m_pTaskModel->delTask(index);

        delete msg;
    }
    else
        QMessageBox::information(this, "Information", "Select row to delete");
}

void MainWindow::on_actionSetting_triggered()
{
    dSetting *pSetting = new dSetting(m_nameStyle, this);
    if(pSetting->exec() == QDialog::Accepted)
    {
        m_nameStyle = pSetting->nameStyle();
        if(!m_nameStyle.isEmpty())
            QApplication::setStyle(m_nameStyle);
    }
    delete pSetting;
}

void MainWindow::on_actionAbout_organizer_triggered()
{
    QString msg1("version: beta 0.9.1.0\n\n"), msg2(" Hudz A. P., 2016");
    QChar cp(169);
    QString msg = msg1 + cp + msg2;
    QMessageBox::about(this,
                      "Organizer",
                      msg);
}
