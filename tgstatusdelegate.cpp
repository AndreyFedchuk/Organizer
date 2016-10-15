// ///////////////////////////////////////////////////
// Copyright © 2016 Andriy Hudz. All rights reserved.
// email: andrey.hudz.90@gmail.com
// https://www.facebook.com/AndreyHudz90
// ///////////////////////////////////////////////////

#include "tgstatusdelegate.h"

tgStatusDelegate::tgStatusDelegate(QObject *parent):QStyledItemDelegate(parent) { }

QWidget *tgStatusDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QComboBox * editor = new QComboBox(parent);
    editor->setAutoFillBackground(true);
    QStringList StatusList = Status::getStatusList();
    editor->addItems(StatusList);
    return editor;
}

void tgStatusDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox * pComboBox = static_cast<QComboBox*>(editor);
    QString str = index.data().toString();
    pComboBox->setCurrentText(str);
}

void tgStatusDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox * pComboBox = static_cast<QComboBox*>(editor);
    model->setData(index, pComboBox->currentText());
}

void tgStatusDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}
