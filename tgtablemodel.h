// ///////////////////////////////////////////////////
// Copyright © 2016 Andriy Hudz. All rights reserved.
// email: andrey.hudz.90@gmail.com
// https://www.facebook.com/AndreyHudz90
// ///////////////////////////////////////////////////

#ifndef TGTABLEMODEL_H
#define TGTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>
#include <QFile>
#include <QFont>
#include <QColor>
#include "target.h"


class tgTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    tgTableModel(QObject * parent = nullptr, const QString path = "data.tg");
    ~tgTableModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void AddRow(target & tg);
    target EditRow(const QModelIndex & index);
    void DelRow(const QModelIndex & index);
    int completedCount();

private:
    QString m_path;
    QList<target> * m_ptargetList;
    QVariant getData(int row, int column) const;

signals:
    void completedCountChanged(int);

};

#endif // TGTABLEMODEL_H
