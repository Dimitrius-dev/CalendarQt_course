#include "taskdata.h"

taskData::taskData(){

}

void taskData::setData(QDate addData, QString addTask)
{
    this->data = addData;
    this->ownItem.setText(addTask);
}
QString taskData::getText(){
    return this->ownItem.text();
}
QDate taskData::getData(){
    return this->data;
}

QListWidgetItem taskData::getOwnItem(){
    return this->ownItem;
}

