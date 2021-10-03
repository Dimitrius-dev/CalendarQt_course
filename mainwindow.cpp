#include "mainwindow.h"

#include "QDebug"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_calendarWidget_clicked();

    colorSelected.setBackground(Qt::green);
    colorUnSelected.setBackground(Qt::white);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_calendarWidget_clicked()
{
    data = ui->calendarWidget->selectedDate();

    //ui->calendarWidget->set
    //QCalendarWidget::paintCell(painter, rect, data);
    //ui->verticalScrollBar->valueChanged(50);
}

void MainWindow::on_verticalScrollBar_actionTriggered()
{
    qDebug()<<"mo";
}


void MainWindow::on_open_triggered()
{

}

void MainWindow::on_save_triggered()
{

}

void MainWindow::on_create_triggered()
{

}

void MainWindow::on_info_triggered()
{
    QMessageBox::information(this, "Program by Dmitrii B.", "VERSION 1.0\nThis program is designed to create your own diary\nSee, more on <style>...</style>https://github.com/Dimitriusprog");
    //вставить гиперссылку
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    for(int i{};i < tasks.size();i++)
    {
        if(item->text() == tasks[i].getText()){
            ui->calendarWidget->setSelectedDate(tasks[i].getData());
            break;
        }
    }
}

void MainWindow::on_addEvent_clicked()
{
    //вызов диалога текстового поля
    //запись
    //
    /*
    for(int i{};i < tasks.size();i++)
    {
        if(ui->calendarWidget->selectedDate().getDate() == tasks[i].getText()){
            ui->calendarWidget->setSelectedDate(tasks[i].getData());
            return;
        }
    }
    */

    bool ok;
    QString text = QInputDialog::getText(this,
                                 QString::fromUtf8("Введите задачу"),
                                 QString::fromUtf8("Ваш текст:"),
                                 QLineEdit::Normal,
                                 QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty()){
        ui->calendarWidget->setDateTextFormat(ui->calendarWidget->selectedDate(),colorSelected);

        taskData data;
        data.setData(ui->calendarWidget->selectedDate(), text);
        tasks.push_back(data);
        ui->listWidget->addItem(text);
        //ui->listWidget->addItem(QString::fromUtf8("%1").arg(text));
    }

    /*
    QString fileName = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath(),
                                "Images (*.txt);;All files (*.*)");
    qDebug()<<fileName;
    */

    //ui->listWidget->addItem();
}

void MainWindow::on_deleteEvent_clicked()
{
    ui->calendarWidget->setDateTextFormat(ui->calendarWidget->selectedDate(),colorUnSelected);
}
