#include "dailytasksmodel.h"

DailyTasksModel::DailyTasksModel(QObject *parent, const QString path)
    : QAbstractTableModel(parent), nCountColumn(static_cast<int>(taskColumn::columnCount)), m_path(path)
{
    m_pList = new QList<task>;

    QFile file;
    file.setFileName(m_path);
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_7);
        in >> *m_pList;
        file.close();
    }
}

DailyTasksModel::~DailyTasksModel()
{
    QFile file;
    file.setFileName(m_path);
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_7);
        out << *m_pList;
        file.close();
    }

    delete m_pList;
}

QVariant DailyTasksModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Vertical)
        return section + 1;
    else
    {
        switch(section)
        {
        case taskColumn::ID:
            return QVariant("№:");
        case taskColumn::Task:
            return QVariant("Task:");
        case taskColumn::Completed:
            return QVariant("Status:");
        case taskColumn::Date:
            return QVariant("Date:");
        default:
            return QVariant();
        }
    }
}

int DailyTasksModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_pList->count();
}

int DailyTasksModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return nCountColumn;
}

QVariant DailyTasksModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        switch(index.column())
        {
        case taskColumn::ID:
            return m_pList->at(index.row()).ID;
        case taskColumn::Task:
            return m_pList->at(index.row()).taskName;
        case taskColumn::Completed:
            if(m_pList->at(index.row()).completed)
                return QVariant("ready");
            else
                return QVariant("NOT ready");
        case taskColumn::Date:
            return m_pList->at(index.row()).date;
        default:
            return QVariant();
        }
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
    default:
        return QVariant();
    }
}

//bool DailyTasksModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (data(index, role) != value && role == Qt::EditRole)
//    {
//        switch(index.column())
//        {
//        case taskColumn::ID:
//            (*m_pList)[index.row()].ID = value.toInt();
//            break;
//        case taskColumn::Task:
//            (*m_pList)[index.row()].taskName = value.toString();
//            break;
//        case taskColumn::Completed:
//            (*m_pList)[index.row()].completed = value.toBool();
//            break;
//        case taskColumn::Date:
//            (*m_pList)[index.row()].date = value.toDate();
//            break;
//        default:
//            return false;
//        }

//        emit dataChanged(index, index, QVector<int>() << role);
//        return true;
//    }
//    return false;
//}

Qt::ItemFlags DailyTasksModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    auto result = QAbstractTableModel::flags(index);
    return result;
}

void DailyTasksModel::addTask(task &ts)
{
    beginInsertRows(QModelIndex(), m_pList->size(), m_pList->size());
    m_pList->push_back(ts);
    endInsertRows();
}

task DailyTasksModel::editTask(QModelIndex &index)
{
    return m_pList->at(index.row());
}

void DailyTasksModel::delTask(QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    m_pList->removeAt(index.row());
    endRemoveRows();
}
