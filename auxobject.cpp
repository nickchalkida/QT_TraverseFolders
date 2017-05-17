#include "auxobject.h"
#include <QThread>

extern int StartThreads(MainWindow *, AuxObject *);

AuxObject::AuxObject(QObject *parent) : QObject(parent)
{

}

void AuxObject::SetTheWindow(MainWindow *wp)
{
    thewin = wp;
}

void AuxObject::DoTheLongJob(MainWindow *wp)
{
    StartThreads(wp,this);
}
