#include <QCoreApplication>
#include <QObject>
#include "controller.h"
#include <QDebug>





int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    Controller c;

    return a.exec();
}
