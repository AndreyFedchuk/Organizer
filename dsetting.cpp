#include "dsetting.h"
#include "ui_dsetting.h"

dSetting::dSetting(QString path, QString strStyle, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dSetting),
    m_dataControlTG(path),
    m_strStyle(strStyle)
{
    ui->setupUi(this);
    ui->comboBox->addItems(QStyleFactory::keys());
    if(!m_strStyle.isEmpty())
        ui->comboBox->setCurrentText(m_strStyle);

    ui->lineEdit->setText(m_dataControlTG);
}

dSetting::~dSetting()
{
    delete ui;
}

QString dSetting::pathAutoControl()
{
    return m_dataControlTG;
}

QString dSetting::nameStyle()
{
    return m_strStyle;
}

void dSetting::on_comboBox_activated(const QString &str)
{
    m_strStyle = str;
}

void dSetting::on_toolButton_clicked()
{
    m_dataControlTG = QFileDialog::getOpenFileName(this, "Chose file to save", "*.tg");
    if(!m_dataControlTG.isEmpty())
    {
        ui->lineEdit->setText(m_dataControlTG);
    }
}
