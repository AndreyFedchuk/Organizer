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
