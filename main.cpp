#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnect();
    MainWindow w;

    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("Gestion des clients"),
                    QObject::tr("Bienvenue !.\n"
                                "Cliquez OK pour remplir vos informations"), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("Gestion des Clients "),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();




}
