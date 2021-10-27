#include "client.h"

Client::Client()
{
num_tel=0; cin=0; nom="";

prenom="", adresse=""; voiture=""; mail="";
}


Client::Client(int num_tel,int cin, QString nom,QString prenom ,QString adresse,QString mail ,QString voiture);

int getnum();
int getcin();
QString getnom();
QString getprenom();
QString getadr();
QString getmail();
QString getvoiture();
{this->num_tel=num_tel; this->cin=cin; this->nom=nom; this->prenom=prenom; this->adresse=adresse; this->mail=mail; this->voiture=voiture}









void setnum(int);
void setcin(int);
void setnom(QString);
void setprenom(QString);
void setadr(QString);
void setmail(QString);
void setvoiture(QString);

