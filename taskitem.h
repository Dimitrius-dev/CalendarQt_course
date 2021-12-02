#ifndef TASKITEM_H
#define TASKITEM_H

#include "QString"
#include "QDate"

class Taskitem
{
public:
    Taskitem(QString name, QDate date);
    Taskitem(QString line);
    QDate getDate();
    QString getItemString();

private:
    QString name;
    QDate date;
};

#endif // TASKITEM_H
