#include "client.h"
#include <QSqlQuery>

Client::Client()
{
num_tel=0; cin=0; nom="";

prenom="", adresse=""; voiture=""; mail="";
}


Client::Client(int num_tel,int cin, QString nom, QString prenom , QString adresse, QString mail  ,QString voiture);

int getnum();
int getcin();
QString getnom();
QString getprenom();
QString getadr();
QString getmail();
QString getvoiture();
{this->num_tel=num_tel; this->cin=cin; this->nom=nom; this->prenom=prenom; this->adresse=adresse; this->mail=mail; this->voiture=voiture}

int Client::getnum(){return num;}
int Client::getcin(){return cin;}
QString Client::getnom(){return nom;}
QString Client::getprenom(){return prenom;}
QString Client::getadr(){return adresse;}
QString Client::getmail(){return mail;}
QString Client::getvoiture(){return voiture;}









void Client:: setnum(int num) {this->num=num;}
void Client::setcin(int cin) {this->cin=cin;}
void Client::setnom(QString nom) {this->nom=nom;}
void Client::setprenom(QString prenom) {this->prenom=prenom;}
void Client::setadr(QString adresse) {this->adresse=adresse;}
void Client::setmail(QString mail) {this->mail;}
void Client::setvoiture(QString voiture) {this->voiture=voiture;}
bool Client::ajouter()
{bool test=false;
    QSqlQuery query;
    QString cin_string=QString::number(cin);
    QString num_string=QString::number(num);

          query.prepare("INSERT INTO client (num,cin,nom,prenom,adresse,mail,voiture) "
                        "VALUES (:num, :cin, :nom, :prenom, :adresse, :mail, :voiture)");
          query.bindValue(":cin", cin_string);
          query.bindValue(":num", num_string);
          query.bindValue("nom", nom);
          query.bindValue("prenom", prenom);
          query.bindValue("adresse", adresse);
          query.bindValue("mail", mail);
          query.bindValue("voiture", voiture);

          query.exec();

return test;
}
