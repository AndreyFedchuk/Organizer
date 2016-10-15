// ///////////////////////////////////////////////////
// Copyright © 2016 Andriy Hudz. All rights reserved.
// email: andrey.hudz.90@gmail.com
// https://www.facebook.com/AndreyHudz90
// ///////////////////////////////////////////////////

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

bool SetProxyParam::inProcess()
{
    return ui->m_pCheckProcess->isChecked();
}

bool SetProxyParam::inWaiting()
{
    return ui->m_pCheckWaiting->isChecked();
}

bool SetProxyParam::Completed()
{
    return ui->m_pCheckCompleted->isChecked();
}

bool SetProxyParam::Deferred()
{
    return ui->m_pCheckDeferred->isChecked();
}
