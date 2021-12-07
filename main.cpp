#include "mainwindow.h"
#include "email.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "menu.h"
#include "firas.h"
//test
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test=c.createconnection();
    menu w;


    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click OK to exit."), QMessageBox::Ok);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click OK to exit."), QMessageBox::Ok);



    return a.exec();
}
