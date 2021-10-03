#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include "QTextCharFormat"
#include <QMainWindow>
#include "taskdata.h"
#include "instdata.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QInputDialog"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calendarWidget_clicked();

    void on_verticalScrollBar_actionTriggered();

    void on_pushButton_clicked();

    void printTask();

    void on_open_triggered();

    void on_save_triggered();

    void on_create_triggered();

    void on_info_triggered();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_addEvent_clicked();

    void on_deleteEvent_clicked();

private:
    Ui::MainWindow *ui;
    //QStringList list;

    QList<taskData> tasks;
    QDate data;

    int pages = 0;
    QString name = "";
    QString today = "";
    bool saved = true;


    QTextCharFormat colorSelected, colorUnSelected;


};
#endif // MAINWINDOW_H
