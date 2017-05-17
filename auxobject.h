#ifndef AUXOBJECT_H
#define AUXOBJECT_H

#include <QObject>

class MainWindow;

class AuxObject : public QObject
{
    Q_OBJECT
public:
    explicit AuxObject(QObject *parent = 0);


signals:
    void SendSomeInfo(QString info);
public slots:
    void SetTheWindow(MainWindow *);
    void DoTheLongJob(MainWindow *);

private:
    MainWindow *thewin;
};

#endif // AUXOBJECT_H
