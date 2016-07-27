#ifndef TGSTATUSDELEGATE_H
#define TGSTATUSDELEGATE_H
#include <QStyledItemDelegate>
#include <QComboBox>
#include "target.h"

class tgStatusDelegate : public QStyledItemDelegate
{
public:
    tgStatusDelegate(QObject * parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // TGSTATUSDELEGATE_H
