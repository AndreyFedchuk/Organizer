#ifndef TARGET_H
#define TARGET_H

enum class Column{Name, Description, Priority, Deadline, Ready};
struct target{
    QString name;
    QString description;
    int priority;
    QString deadline;
    bool ready;
};



#endif // TARGET_H
