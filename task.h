// ///////////////////////////////////////////////////
// Copyright © 2016 Andriy Hudz. All rights reserved.
// email: andrey.hudz.90@gmail.com
// https://www.facebook.com/AndreyHudz90
// ///////////////////////////////////////////////////

#ifndef TASK_H
#define TASK_H

#include <QDataStream>
#include <QDate>

enum class taskColumn{
    ID,
    Task,
    Completed,
    Date,
    columnCount
};

struct task{
    quint32 ID;
    QString taskName;
    bool completed;
    QDate date;
};

inline QDataStream &operator << (QDataStream &stream, const task &Task)
{
    stream << Task.ID;
    stream << Task.taskName;
    quint32 Bool = static_cast<quint32>(Task.completed);
    stream << Bool;
    stream << Task.date;
    return stream;
}

inline QDataStream &operator >> (QDataStream &stream, task &Task)
{
    stream >> Task.ID;
    stream >> Task.taskName;
    quint32 Bool;
    stream >> Bool;
    Task.completed = static_cast<bool>(Bool);
    stream >> Task.date;
    return stream;
}

#endif // TASK_H
