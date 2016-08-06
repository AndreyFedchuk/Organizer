#include "dailytasks.h"
#include "ui_dailytasks.h"

DailyTasks::DailyTasks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DailyTasks)
{
    //base Param
    ui->setupUi(this);
    m_pTaskModel = new DailyTasksModel(this);
    m_pProxy = new QSortFilterProxyModel(this);
    m_pProxy->setSourceModel(m_pTaskModel);
    m_pProxy->setFilterKeyColumn(static_cast<int>(taskColumn::Date));
    ui->tableView->setModel(m_pProxy);
    ui->tableView->setSortingEnabled(true);
    m_pProxy->sort(static_cast<int>(taskColumn::ID));
    ui->progressBarTask->setRange(0, m_pTaskModel->rowCount());
    ui->progressBarTask->setValue(m_pTaskModel->getCountCompleted());

    //Setting to view
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    QHeaderView * header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeToContents);
    header->setSectionResizeMode(static_cast<int>(taskColumn::Task), QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setHidden(true);
    ui->calendarWidget->setSelectedDate(QDate::currentDate());
}

DailyTasks::~DailyTasks()
{
    delete ui;
    delete m_pProxy;
    delete m_pTaskModel;
}
void DailyTasks::on_calendarWidget_clicked(const QDate &date)
{
    m_pProxy->setFilterRegExp(date.toString("yyyy-MM-dd"));
    ui->tableView->setColumnHidden(static_cast<int>(taskColumn::Date), true);
    ui->tableView->resizeRowsToContents();

    //to progressBar
    if(m_pProxy->rowCount())
    {
        int nCountCompleted(0);
        QModelIndex index;
        for(int i(0); i < m_pProxy->rowCount(); ++i)
        {
            index =  m_pProxy->index(i, static_cast<int>(taskColumn::Completed));
            if(index.isValid())
            {
                if(index.data().toString() == "ready")
                    ++nCountCompleted;
            }
            else
                break;
        }
        ui->progressBarTask->setRange(0, m_pProxy->rowCount());
        ui->progressBarTask->setValue(nCountCompleted);
    }
    else
    {
        ui->progressBarTask->setRange(0, 1);
        ui->progressBarTask->setValue(0);
    }
}

void DailyTasks::on_m_pbtnAdd_clicked()
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
        ui->tableView->resizeRowsToContents();
    }
    delete pDialog;
}

void DailyTasks::on_m_pbtnEdit_clicked()
{
    QModelIndex index = m_pProxy->mapToSource(ui->tableView->selectionModel()->currentIndex());
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
            ui->tableView->resizeRowsToContents();
        }
        delete pDialog;
    }
    else
        QMessageBox::information(this, "Information", "Select row to edite");
}

void DailyTasks::on_m_pbtnDel_clicked()
{
    QModelIndex index = m_pProxy->mapToSource(ui->tableView->selectionModel()->currentIndex());
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
        {
            m_pTaskModel->delTask(index);
        }
        delete msg;
    }
    else
        QMessageBox::information(this, "Information", "Select row to delete");
}
