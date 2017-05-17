#include "mainwindow.h"
#include "ui_mainwindow.h"

extern int StartThreads(MainWindow *, AuxObject *);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(
                &myauxobject,
                &AuxObject::SendSomeInfo,//(QString),
                this,
                &MainWindow::slotformessage//(QString))
                );
    myauxobject.SetTheWindow(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    appmdir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                  "/home",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEdit->setText(appmdir);

    //QFuture<void> test = QtConcurrent::run(&this->myauxobject, &AuxObject::DoTheLongJob, this);

    StartThreads(this,NULL);

}

void MainWindow::slotformessage(QString item) {

    ui->listWidget->insertItem(0,item);

    //ui->listWidget->addItem(item);

    //while (qApp->hasPendingEvents())
    //    qApp->processEvents();

}



