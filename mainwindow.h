#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "taskitem.h"
#include "QTextCharFormat"
#include <QMainWindow>
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

    void printTasks(bool ignore);

    void sort();

    void clearAll();

    void on_open_triggered();

    void on_save_triggered();

    void on_create_triggered();

    void on_info_triggered();

    void on_addEvent_clicked();

    void on_deleteEvent_clicked();

    void on_spinBox_textChanged();

    void on_saveHow_triggered();

private:
    Ui::MainWindow *ui;
    //QStringList list;

    QDate date;

    int pages = 0;
    QString name = "";
    QString today = "";
    bool saved = true;

    QString nameOfFile = "";

    QTextCharFormat colorSelected, colorUnSelected, colorHighlight;

    QList<taskitem>::iterator iterList;
    QList<taskitem> tasks;

    bool change = false;
};
#endif // MAINWINDOW_H
