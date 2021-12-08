#ifndef CARTE_H
#define CARTE_H
#include"connection.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QSqlQueryModel>



class carte
{
public:
    carte();
    carte(QString,QString);


    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer();
    bool update();
    QString  recherchee();

    //sett
    void setcin(QString);

private:
    QString point ;
    QString cin;
};

#endif // CARTE_H
