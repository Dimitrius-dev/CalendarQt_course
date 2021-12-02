#include "taskitem.h"
#include "QDebug"

Taskitem::Taskitem(QString name, QDate date)
{
    this->name = name;
    this->date = date;
}

QString Taskitem::getItemString()
{
    return QString::number(date.day()) + ":" + QString::number(date.month()) + ":" +  QString::number(date.year()) + ":" + " " + name;
}

Taskitem::Taskitem(QString line)
{
    int el[3];
    int iter = 0;

    bool ok;
    for(int i = 0;i<3;i++)
    {
        el[i] = line.mid(iter,line.indexOf(":",iter) - iter).toInt(&ok);
        iter = line.indexOf(":",iter) + 1;
    }

    if(!ok)
    {
        qDebug()<<"error toInt setItemString";
        //qDebug()<<el[2]<<el[1]<<el[0];
    }
    else
    {
        date.setDate(el[2],el[1],el[0]);
        name = line.mid(iter + 1, line.length() - iter);
        //qDebug()<<date.toString();
        //qDebug()<<"="<<name<<"=";
    }
}

QDate Taskitem::getDate()
{
    return  date;
}
