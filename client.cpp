#include "client.h"




Client::Client(int cin, int num ,QString nom, QString prenom,QString addresse,QString mail,QString matricule)
{
    this->CIN=cin;
    this->NOM=nom;
    this->NUM=num;
    this->PRENOM=prenom;
    this->ADDRESSE=addresse;
    this->MAIL=mail;
    this->MATRICULE=matricule;


}
bool Client::ajouter()
{
QSqlQuery query;

QString res1=QString::number(CIN);
QString res2=QString::number(NUM);
query.prepare("INSERT INTO CLIENT(CIN,NOM,PRENOM,ADRESSE,NUMERO_TEL,MATRICULE_VOITURE,MAIL)""VALUES(:cin,:nom,:prenom,:adresse,:numero_tel,:matrcule_voiture,:mail)");
query.bindValue(0,res1);
query.bindValue(1,res2);
query.bindValue(2,NOM);
query.bindValue(3,PRENOM);
query.bindValue(4,ADDRESSE);
query.bindValue(5,MAIL);
query.bindValue(6,MATRICULE);





return query.exec();



}

bool Client::supprimer( int cin)
{
QSqlQuery query;
QString res2=QString::number(cin);

query.prepare("delete from CLIENT where CIN= :cin");
query.bindValue(":cin",cin);
return query.exec();
}
QSqlQueryModel*Client::afficher()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from CLIENT");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NUM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("ADDRESSE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("MATRICULE"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("MAIL"));
return model;
}

QSqlQueryModel*Client::afficherjoin()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from CLIENT INNER JOIN VOITURE ON CLIENT.MATRICULE_VOITURE = VOITURE.MATRICULE");
/*model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NUM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("ADDRESSE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("MATRICULE"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("MAIL"));*/
return model;
}

bool Client::modifier(int cin)
{
     QSqlQuery query;
     QString r1= QString::number(cin);

    query.prepare("UPDATE CLIENT SET CIN=:cin ,NOM=:nom,PRENOM=:prenom,ADRESSE=:adresse,NUMERO_TEL=:numero_tel,MATRICULE_VOITURE=:matricule,MAIL=:mail WHERE CIN=:cin");
    query.bindValue(":cin",r1);
    query.bindValue(1,NUM);

    query.bindValue(2,NOM);
    query.bindValue(3,PRENOM);
    query.bindValue(4,ADDRESSE);
    query.bindValue(5,MATRICULE);
    query.bindValue(6,MAIL);
    return query.exec();

}

QSqlQueryModel *Client::tri()
{QSqlQueryModel *model=new QSqlQueryModel();

model->setQuery("select * from client order by cin");
            return model;



}




QSqlQueryModel *Client::rechercher(QString cinn)
{
    // QString res= QString::number(cinn);
     QSqlQueryModel *model=new QSqlQueryModel();
      model->setQuery("select * from CLIENT where CIN LIKE '"+cinn+"%'" );

    /*  model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("NUM"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRENOM"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("ADRESSE"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("MATRICULE"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("MAIL"));

*/

      return model; }
