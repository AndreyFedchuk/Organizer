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
    explicit dSetting(QString path = nullptr, QString strStyle = nullptr, QWidget *parent = nullptr);
    ~dSetting();
    QString pathAutoControl();
    QString nameStyle();

private slots:
    void on_comboBox_activated(const QString &str);
    void on_toolButton_clicked();

private:
    Ui::dSetting *ui;
    QString m_dataControlTG;
    QString m_strStyle;
};

#endif // DSETTING_H
