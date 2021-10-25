#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
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
    bool employe::supprimer(int)
    {
        QSqlQuery query;
        QString id_string=QString::number(id);
        query.prepare("DELETE FROM employe WHERE Id = :id");
        query.bindValue(":id", id_string);
        return query.exec();
    }
    QSqlQueryModel* employe::afficher()
    {
        QSqlQueryModel *model = new QSqlQueryModel;
              model->setQuery("SELECT* FROM employe");
              model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("email"));
              model->setHeaderData(4, Qt::Horizontal, QObject::tr("fonction"));
              model->setHeaderData(5, Qt::Horizontal, QObject::tr("salaire"));
              return model;
    }
    bool employe::editer(){
        QSqlQuery query;
        QString r= QString::number(id);
        query.prepare("UPDATE employe SET id=:id,nom=:nom,prenom=:prenom WHERE id=:id");
       query.bindValue(":id",r);
       query.bindValue(":nom",nom);
       query.bindValue(":prenom",prenom);


        return query.exec();
    }
    void employe::rechercher_emp(QTableView * table,QString id)
    {
        QSqlQueryModel *model=new QSqlQueryModel();
        QSqlQuery *query =new QSqlQuery();
        query->prepare("select * from employe where regexp_like(id,:id);");
        query->bindValue(":id",id);
        query->exec();
        model->setQuery(*query);
        table->setModel(model);
        table->show();
    }
    void employe::clear(QTableView *table)
    {
        QSqlQueryModel *model=new QSqlQueryModel();
        model->clear();
        table->setModel(model);
    }


