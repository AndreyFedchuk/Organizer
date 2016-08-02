#include "dialogdailytask.h"
#include "ui_dialogdailytask.h"

dialogDailyTask::dialogDailyTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogDailyTask)
{
    ui->setupUi(this);

    ui->m_pDate->setDate(QDate::currentDate());
}

dialogDailyTask::~dialogDailyTask()
{
    delete ui;
}

quint32 dialogDailyTask::getID()
{
    return ui->m_pspinBoxID->value();
}

void dialogDailyTask::setID(quint32 &id)
{
    ui->m_pspinBoxID->setValue(id);
}

QString dialogDailyTask::getTask()
{
    return ui->m_ptxtEdit->toPlainText();
}

void dialogDailyTask::setTask(QString &str)
{
    ui->m_ptxtEdit->setText(str);
}

QDate dialogDailyTask::getDate()
{
    return ui->m_pDate->date();
}

void dialogDailyTask::setDate(QDate &date)
{
    ui->m_pDate->setDate(date);
}

bool dialogDailyTask::getCompleted()
{
    return ui->m_pCheck->isChecked();
}

void dialogDailyTask::setCompleted(bool enable)
{
    ui->m_pCheck->setChecked(enable);
}
