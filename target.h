#ifndef TARGET_H
#define TARGET_H
#include <QDate>

enum class Column{Name, Description, Priority, Deadline, Ready, columnCount};
struct target{

    QString name;
    QString description;
    int priority;
    QDate deadline;
    bool ready;
};

#endif // TARGET_H
