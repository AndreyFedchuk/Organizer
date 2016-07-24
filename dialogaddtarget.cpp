#include "dialogaddtarget.h"
#include "ui_dialogaddtarget.h"

dialogAddTarget::dialogAddTarget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogAddTarget)
{
    ui->setupUi(this);
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
