#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
employe::employe()
{
    id=0;
    nom="";
    prenom="";
    email="";
    fonction="";
    salaire="";

}
employe::employe(int id,QString nom,QString prenom,QString email,QString fonction,QString salaire)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->fonction=fonction;
    this->salaire=salaire;
}
    int employe::getid(){return id;}
    QString employe::getnom(){return nom;}
    QString employe::getprenom(){return prenom;}
    QString employe::getemail(){return email;}
    QString employe::getfonction(){return fonction;}
    QString employe::getsalaire(){return salaire;}
    void employe::setid(int id){this->id=id;}
    void employe::setnom(QString nom){this->nom=nom;}
    void employe::setprenom(QString prenom){this->prenom=prenom;}
    void employe::setemail(QString email){this->email=email;}
    void employe::setfonction(QString fonction){this->fonction=fonction;}
    void employe::setsalaire(QString salaire){this->salaire=salaire;}
    bool employe::ajouter()
    {

                QSqlQuery query;
                QString id_string=QString::number(id);
                     query.prepare("INSERT INTO employe (id, nom, prenom, email,fonction,salaire) "
                                   "VALUES (:id, :nom, :prenom, :email, :fonction, :salaire)");
                     query.bindValue(":id", id_string);
                     query.bindValue(":nom", nom);
                     query.bindValue(":prenom", prenom);
                     query.bindValue(":email", email);
                     query.bindValue(":fonction", fonction);
                     query.bindValue(":salaire", salaire);




        return query.exec();
    }

