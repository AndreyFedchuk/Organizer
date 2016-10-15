// ///////////////////////////////////////////////////
// Copyright © 2016 Andriy Hudz. All rights reserved.
// email: andrey.hudz.90@gmail.com
// https://www.facebook.com/AndreyHudz90
// ///////////////////////////////////////////////////

#ifndef SETPROXYPARAM_H
#define SETPROXYPARAM_H

#include <QDialog>

namespace Ui {
class SetProxyParam;
}

class SetProxyParam : public QDialog
{
    Q_OBJECT

public:
    explicit SetProxyParam(QWidget *parent = nullptr);
    ~SetProxyParam();

    bool inProcess();
    bool inWaiting();
    bool Completed();
    bool Deferred();

private:
    Ui::SetProxyParam *ui;
};

#endif // SETPROXYPARAM_H
