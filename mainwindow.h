#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include <windows.h>

#include "auxobject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString appmdir;

private slots:
    void on_pushButton_clicked();
public slots:
    void slotformessage(QString);
signals:
private:
    Ui::MainWindow *ui;
    AuxObject myauxobject;
};

#endif // MAINWINDOW_H
