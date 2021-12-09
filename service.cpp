#include "service.h"
#include <QSqlQuery>
#include<QTime>
#include <QSqlError>
#include <QSqlError>
#include <QtDebug>

service::service()
{
     id=0;
    QString nom="";
     cout =0;
     duree=0;
     disponibilite="";
}

service::service(int id,QString nom,int cout,int duree,QString disponibilite){
    this->id=id;
    this->nom=nom;
    this->cout=cout;
    this->duree = duree;
    this->disponibilite = disponibilite;
}
bool service::ajouter(){
    QSqlQuery query;
   QString idd = QString::number(id);
   QString res=QString::number(cout);
   QString dur = QString::number(duree);
    query.prepare("INSERT INTO service (nom,cout,duree,id_emp,disponibilite)"
                "Values(:nom,:cout,:duree,:id,:disponibilite)");
    query.bindValue(":nom",nom);
    query.bindValue(":cout",res);
    query.bindValue(":duree",dur);
    query.bindValue(":id",idd);
    query.bindValue(":disponibilite",disponibilite);
  qDebug()<< query.lastError();
          return  query.exec();
}

QSqlQueryModel * service::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM service order by nom ");
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_EMP"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("COUT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("duree"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("disponibilite"));

    return model;
}

bool service::supprimer(int id)
{
     QString res=QString::number(id);
    QSqlQuery query;
    query.prepare("Delete from service where id=:id ");
    query.bindValue(":id",res);
    return query.exec();
}
bool service::modifier(int id){
    QString res=  QString::number(cout);
    QString dur = QString::number(duree);
    QSqlQuery query;
    query.prepare("update service set nom=:nom,cout=:cout,duree=:duree,disponibilite=:disponibilite "
                    "  where id_emp=:id");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":cout",res);
    query.bindValue(":duree",duree);
    query.bindValue(":disponibilite",disponibilite);
   return  query.exec();
}
QSqlQueryModel * service::afficherRech(QString res)
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select * from service where id like'"+res+"%' or nom like'"+res+"%' or cout like'"+res+"%' or disponibilite like'"+res+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("COUT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("duree"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("disponibilite"));
    return model;
}
QString service::apercu_pdf()
 {
     QString text="             ** La Listes Des services **       \n \n " ;
     QSqlQuery query ;
     QString i;
     QString d;
     QString e,c,h,g;
     int inc = 0;
      query.exec("SELECT * FROM SERVICES");
      while (query.next())
      {
         i=query.value(0).toString();
         d=query.value(1).toString();
         e=query.value(2).toString();
         c=query.value(3).toString();
         g=query.value(4).toString();
         inc++;
         char numstr[21]; // enough to hold all numbers up to 64-bits
         QString result = itoa(inc, numstr, 10);
         text += "\n SERVICES: "+result+"\n\n  - Nom Livreur: "+ i+"\n  - Nom Equipement: "+d+"\n  - Nom Client: "+e+"\n  - Id Colis: "+c+"\n  - Date_Livraison: "+g+"\n\n_________________________\n";

     }

             return text ;
 }
QSqlQueryModel * service::trier_nom()
{
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("Select * from services \
                         Order by ID ASC");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("COUT"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("duree"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("disponibilite"));
     return model;
}
