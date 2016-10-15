// ///////////////////////////////////////////////////
// Copyright © 2016 Andriy Hudz. All rights reserved.
// email: andrey.hudz.90@gmail.com
// https://www.facebook.com/AndreyHudz90
// ///////////////////////////////////////////////////

#ifndef TGPRIORITYDELEGATE_H
#define TGPRIORITYDELEGATE_H

#include <QApplication>
#include <QStyledItemDelegate>
#include <QSlider>
#include <QProgressBar>


class tgPriorityDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit tgPriorityDelegate(QObject * parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget * editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // TGPRIORITYDELEGATE_H
