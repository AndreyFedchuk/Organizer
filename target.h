#ifndef TARGET_H
#define TARGET_H
#include <QObject>
#include <QDate>
#include <QMap>

enum class Column{Name, Description, Priority, Deadline, Ready, columnCount};

class Status: public QObject
{
    Q_OBJECT

public:
    explicit Status(QObject * parent = nullptr): QObject(parent){}
    enum class Value{in_waiting, deferred, completed, in_process, nVariant};
    Q_ENUM(Value)

    static QString to_string(Status::Value ready)
    {
        switch(ready)
        {
        case Status::Value::completed:
            return "completed";
        case Status::Value::deferred:
            return "deferred";
        case Status::Value::in_process:
            return "in process";
        case Status::Value::in_waiting:
            return "in waiting";
        default:
            return "error";
        }
    }
    static Status::Value from_string(const QString str)
    {
        static const QMap<QString, Status::Value> enumStringMap = {{"in waiting", Status::Value::in_waiting},
                                                                  {"in process", Status::Value::in_process},
                                                                  {"completed", Status::Value::completed},
                                                                  {"deferred", Status::Value::deferred}};
        auto it = enumStringMap.find(str);
        if(it == enumStringMap.end())
            return Status::Value::nVariant;
        return it.value();
    }
    static QStringList getStatusList()
    {
        QStringList StatusList;
        StatusList << "in waiting"
                   << "in process"
                   << "completed"
                   << "deferred";
        return StatusList;
    }
};

struct target{
    QString name;
    QString description;
    int priority;
    QDate deadline;
    Status::Value ready;
};

#endif // TARGET_H
