#include "tgtablemodel.h"

tgTableModel::tgTableModel(QObject *parent): QAbstractTableModel(parent)
{
    //test ////////////////////////////////
    target tg;
    tg.name = "Реализовать органайзер";
    tg.description = "добавить установщик";
    tg.priority = 50;
    tg.ready = false;
    tg.deadline = QDate(2016, 8, 1);

    m_ptargetList = new QList<target>;
    m_ptargetList->push_back(tg);

    tg.name = "Посмотреть бокс";
    tg.description = "Постол Кроуфорд";
    tg.priority = 100;
    tg.ready = false;
    tg.deadline = QDate(2016, 7, 23);

    m_ptargetList->push_back(tg);
    // /////////////////////////////////////
}

tgTableModel::~tgTableModel()
{
    delete m_ptargetList;
}

int tgTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_ptargetList->count();
}

int tgTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return (int)Column::columnCount;
}

QVariant tgTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int row = index.row();
    int column = index.column();

    switch(role)
    {
    case Qt::DisplayRole:
        return getData(row, column);
    case Qt::EditRole:
        return getData(row, column);

    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
    case Qt::BackgroundRole:
        if(m_ptargetList->at(row).ready)
            return QColor(Qt::gray);
        if(m_ptargetList->at(row).priority > 75)
            return QColor(Qt::red);
        if(m_ptargetList->at(row).priority > 50)
            return QColor(Qt::yellow);
        if(m_ptargetList->at(row).priority > 25)
            return QColor(Qt::green);
        else
            return QColor(Qt::blue);
    case Qt::FontRole:
        return QFont("Times", 10);

    default:
        return QVariant();
    }
}

QVariant tgTableModel::getData(int row, int column) const
{
    switch(column)
    {
    case Column::Name:
        return m_ptargetList->at(row).name;
    case Column::Description:
        return m_ptargetList->at(row).description;
    case Column::Priority:
        return m_ptargetList->at(row).priority;
    case Column::Deadline:
        return m_ptargetList->at(row).deadline;
    case Column::Ready:
        return m_ptargetList->at(row).ready;
    default:
        return QVariant();
    }
}

void tgTableModel::slotAddRow(target &tg)
{
    beginInsertRows(QModelIndex(), m_ptargetList->size(), m_ptargetList->size());
    m_ptargetList->push_back(tg);
    endInsertRows();
}

void tgTableModel::slotDelRow(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());

    m_ptargetList->removeAt(index.row());

    endRemoveRows();
}

target tgTableModel::slotEditRow(const QModelIndex &index)
{
    target tg = m_ptargetList->at(index.row());
    return tg;
}


bool tgTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        // указатель на нужную строку
        target * pTarget = &(*m_ptargetList)[index.row()];

        switch(index.column())
        {
        case Column::Name:
            pTarget->name = value.toString();
            break;
        case Column::Description:
            pTarget->description = value.toString();
            break;
        case Column::Priority:
            pTarget->priority = value.toInt();
            break;
        case Column::Deadline:
            pTarget->deadline = value.toDate();
            break;
        case Column::Ready:
            pTarget->ready = value.toBool();
            break;
        default:
            return false;
        }
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

QVariant tgTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Vertical)
        return section + 1;

    else
        switch(section)
        {
        case Column::Name:
            return QVariant("Target");
        case Column::Description:
            return QVariant("Descriptions");
        case Column::Priority:
            return QVariant("Priority");
        case Column::Deadline:
            return QVariant("Deadline");
        case Column::Ready:
            return QVariant("Ready/Not ready");
        default:
            return QVariant();
        }
}

Qt::ItemFlags tgTableModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;

    auto result = QAbstractTableModel::flags(index);
    return result | Qt::ItemIsEditable;
}
