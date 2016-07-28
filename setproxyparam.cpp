#include "setproxyparam.h"
#include "ui_setproxyparam.h"

SetProxyParam::SetProxyParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetProxyParam)
{
    ui->setupUi(this);
}

SetProxyParam::~SetProxyParam()
{
    delete ui;
}
