#ifndef DSETTING_H
#define DSETTING_H

#include <QDialog>
#include <QFileDialog>
#include <QStyleFactory>

namespace Ui {
class dSetting;
}

class dSetting : public QDialog
{
    Q_OBJECT

public:
    explicit dSetting(QString strStyle = nullptr, QWidget *parent = nullptr);
    ~dSetting();
    QString nameStyle();

private slots:
    void on_comboBox_activated(const QString &str);

private:
    Ui::dSetting *ui;
    QString m_strStyle;
};

#endif // DSETTING_H
