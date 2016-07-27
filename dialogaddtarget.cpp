#include "dialogaddtarget.h"
#include "ui_dialogaddtarget.h"

dialogAddTarget::dialogAddTarget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogAddTarget)
{
    ui->setupUi(this);
    QStringList StatusList = Status::getStatusList();
    ui->m_pcmboBoxStatus->addItems(StatusList);
}

dialogAddTarget::~dialogAddTarget()
{
    delete ui;
}

QString dialogAddTarget::Target()
{
    return ui->m_ptxtTarget->text();
}

QString dialogAddTarget::Description()
{
    return ui->m_ptxtDesc->toPlainText();
}

int dialogAddTarget::Priority()
{
    return ui->m_plcdPrior->value();
}

QDate dialogAddTarget::Deadline()
{
    return ui->m_pDateDeadline->date();
}

Status::Value dialogAddTarget::getStatus()
{
    return Status::from_string(ui->m_pcmboBoxStatus->currentText());
}

void dialogAddTarget::setTarget(const QString str)
{
    ui->m_ptxtTarget->setText(str);
}

void dialogAddTarget::setDescription(const QString str)
{
    ui->m_ptxtDesc->setText(str);
}

void dialogAddTarget::setPriority(const int priority)
{
    ui->m_psldPrior->setValue(priority);
}

void dialogAddTarget::setDeadline(const QDate date)
{
    ui->m_pDateDeadline->setDate(date);
}

void dialogAddTarget::setStatus(Status::Value val)
{
    QString str = Status::to_string(val);
    ui->m_pcmboBoxStatus->setCurrentText(str);
}

