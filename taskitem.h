#ifndef TASKITEM_H
#define TASKITEM_H

#include "QString"
#include "QDate"

class taskitem
{
public:
    taskitem(QString name, QDate date);

    taskitem(QString line);

    QDate getDate();

    QString getItemString();



private:
    QString name;
    QDate date;
};

#endif // TASKITEM_H
