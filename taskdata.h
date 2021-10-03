#ifndef TASKDATA_H
#define TASKDATA_H

#include "QString"
#include "QDate"
#include "QListWidgetItem"

class taskData
{
private:
    QDate data;
    QListWidgetItem ownItem;
public:
    taskData();

    QString getText();

    QDate getData();

    QListWidgetItem getOwnItem();

    void setData(QDate addData, QString addTask);
};

#endif // TASKDATA_H
