#ifndef TGTABLEMODEL_H
#define TGTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>

#include <QFont>      //  ???
#include <QColor>     //  ???

#include "target.h"


class tgTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    tgTableModel(QObject * parent = nullptr);
    ~tgTableModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QList<target> * m_ptargetList;
    QVariant getData(int row, int column) const;
};

#endif // TGTABLEMODEL_H
