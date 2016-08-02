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

    //Setting to view
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    //ui->tableView->setColumnHidden(static_cast<int>(taskColumn::Date), true);
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
