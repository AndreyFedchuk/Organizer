#ifndef DAILYTASKSMODEL_H
#define DAILYTASKSMODEL_H

#include <QAbstractTableModel>

#include <QList>
#include <QFile>

#include "task.h"
#include <QDebug>
#include <QDir>

class DailyTasksModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DailyTasksModel(QObject *parent = nullptr, const QString path = "data.task");
    ~DailyTasksModel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;


    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    //bool setData(const QModelIndex &index, const QVariant &value,
    //             int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void addTask(task &ts);
    task editTask(QModelIndex &index);
    void delTask(QModelIndex &index);

private:
   QList<task> * m_pList;
   int nCountColumn;
   QString m_path;
};

#endif // DAILYTASKSMODEL_H
