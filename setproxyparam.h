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
    explicit SetProxyParam(QWidget *parent = 0);
    ~SetProxyParam();

private:
    Ui::SetProxyParam *ui;
};

#endif // SETPROXYPARAM_H