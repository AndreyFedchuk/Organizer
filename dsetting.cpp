#include "dsetting.h"
#include "ui_dsetting.h"

dSetting::dSetting(QString strStyle, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dSetting),
    m_strStyle(strStyle)
{
    ui->setupUi(this);
    ui->comboBox->addItems(QStyleFactory::keys());
    if(!m_strStyle.isEmpty())
        ui->comboBox->setCurrentText(m_strStyle);
}

dSetting::~dSetting()
{
    delete ui;
}

QString dSetting::nameStyle()
{
    return m_strStyle;
}

void dSetting::on_comboBox_activated(const QString &str)
{
    m_strStyle = str;
}
