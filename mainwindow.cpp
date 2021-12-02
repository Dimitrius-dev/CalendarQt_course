#include "mainwindow.h"

#include "QDebug"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Ежедневник");
    //date = ui->calendarWidget->selectedDate();
    on_calendarWidget_clicked();

    colorSelected.setBackground(Qt::green);
    colorUnSelected.setBackground(Qt::white);
    colorHighlight.setBackground(Qt::red);

    ui->spinBox->setMaximum(0);

    nameOfFile = "Безымянный";
    ui->fileName->setText(nameOfFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calendarWidget_clicked()
{
    date = ui->calendarWidget->selectedDate();
}


void MainWindow::on_open_triggered()
{
    if(change)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, QString::fromUtf8("Внимание"),
                              QString::fromUtf8("Сохранить файл " + nameOfFile.toUtf8() + " ?" ),
                              QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes)
            on_saveHow_triggered();
        else if (reply == QMessageBox::No)
        {

        }
    }

    change = false;


    QString fileName = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath(),
                                "Documents (*.txt);;All files (*.*)");

    if(fileName.isEmpty()){
        return;
    }

    clearAll();

    //qDebug()<<fileName;
    nameOfFile = fileName.right(fileName.length() - fileName.lastIndexOf("/") - 1);
    ui->fileName->setText(nameOfFile);

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Cannot open file for reading"); // если файл не найден, то выводим предупреждение и завершаем выполнение программы
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        tasks.append(Taskitem(line));
        //out << line << endl;
    }
    file.close();

    for(int i = 0;i < tasks.size();i++)//подсвечиваем даты
    {
        ui->calendarWidget->setDateTextFormat(tasks[i].getDate(),colorSelected);
    }
    printTasks(true);
}

void MainWindow::on_create_triggered()
{
    if(change)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, QString::fromUtf8("Внимание"),
                              QString::fromUtf8("Сохранить файл " + nameOfFile.toUtf8() + " ?" ),
                              QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes)
            on_saveHow_triggered();//нюанс с тем, если файл до этого был уже сохранен, то все равно ему предложат новое место для хранения
        else if (reply == QMessageBox::No)
        {

        }
    }

    change = false;

    on_saveHow_triggered();

    clearAll();

}

void MainWindow::sort()
{
    for(int i = tasks.size() - 1;i >= 0; i--)
    {
        for(int j = tasks.size() - 1;j >= 0; j--)
        {
            if(tasks[j].getDate() < tasks[i].getDate())
            {
                tasks.swapItemsAt(i,j);
            }
        }
    }
}

void MainWindow::printTasks(bool ignore){

    if((!change)&&(!ignore))
    {
        change = true;
        ui->fileName->setText("*" + nameOfFile);
    }

    int size = tasks.size();
    ui->spinBox->setMaximum( (size == 0) ? size : size - 1 );
    ui->spinBox->setValue(0);

    ui->textBrowser->clear();
    //if(tasks ==  nullptr){}

    sort();


    for(int i = 0;i<tasks.size();i++)
    {
        ui->textBrowser->append(tasks[i].getItemString());
    }

}

void MainWindow::on_info_triggered()
{
    QMessageBox::information(this, "info", "VERSION 0.0.6\nThis program is designed to create\nyour own diary\nSee more on https://github.com/Dimitriusprog");
    //вставить гиперссылку
}


void MainWindow::on_addEvent_clicked()
{
    for(int i = 0;i<tasks.size();i++)
    {
        if(tasks[i].getDate() == ui->calendarWidget->selectedDate())
        {
            return;
        }
    }

    bool ok;
    QString text = QInputDialog::getText(this,
                                 QString::fromUtf8("Введите задачу"),
                                 QString::fromUtf8("Ваш текст:"),
                                 QLineEdit::Normal,
                                 "", &ok);//QDir::home().dirName()
    if (ok && !text.isEmpty())
    {
        ui->calendarWidget->setDateTextFormat(ui->calendarWidget->selectedDate(),colorSelected);
        tasks.append(Taskitem(text, ui->calendarWidget->selectedDate()));
        printTasks(false);
    }
}

void MainWindow::on_deleteEvent_clicked()
{
    for (iterList = tasks.begin(); iterList != tasks.end(); iterList++)
    {
        if(iterList->getDate() == ui->calendarWidget->selectedDate())
        {
            ui->calendarWidget->setDateTextFormat(ui->calendarWidget->selectedDate(),colorUnSelected);
            tasks.erase(iterList);

            printTasks(false);

            break;
        }
    }

}

void MainWindow::on_spinBox_textChanged()
{
    ui->calendarWidget->setSelectedDate(tasks[ui->spinBox->value()].getDate());
}

void MainWindow::on_saveHow_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this,
                                QString::fromUtf8("Сохранить файл"),
                                QDir::currentPath(),
                                "Documents (*.txt);;All files (*.*)");

    if(fileName.isEmpty())
    {
        return;
    }

    nameOfFile = fileName.right(fileName.length() - fileName.lastIndexOf("/") - 1);
    ui->fileName->setText(nameOfFile);
    change = false;

    QTextStream out(stdout);

    QFile file(fileName);

    // Открываем файл в режиме "Только для записи"
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file); // поток записываемых данных направляем в файл

        for(int i = 0;i<tasks.size(); i++)
        {
            out<<tasks[i].getItemString()<<Qt::endl;
        }

    } else {
        qWarning("Could not open file");
      }
      file.close();
}


void MainWindow::clearAll()
{
    for(int i = 0;i < tasks.size();i++)//подсвечиваем даты
    {
        ui->calendarWidget->setDateTextFormat(tasks[i].getDate(),colorUnSelected);
    }
    ui->textBrowser->clear();
    tasks.clear();
}
