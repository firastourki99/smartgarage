#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QTableView>


class Client
{
private:
    QString NOM, PRENOM,ADDRESSE,MAIL,MATRICULE;
    int CIN;
    int NUM;

public:
    Client(){}
    Client(int,int,QString,QString,QString,QString,QString);
    QString getnom(){return NOM;}
    QString getprenom(){return PRENOM;}
    QString getadresse(){return ADDRESSE;}
    QString getmail(){return MAIL;}
    QString getmatricule (){return MATRICULE;}
    int getcin(){return CIN;}
    int getnum(){return NUM;}


    void setnom(QString nom){NOM=nom;}
    void setadresse(QString adresse){ADDRESSE=adresse;}
    void setmail(QString mail){MAIL=mail;}
    void setmatricule(QString matricule){MATRICULE=matricule;}
    void setprenom(QString prenom){PRENOM=prenom;}
    void setcin(int cin){this->CIN=cin;};
    void setnum (int num){this->NUM=num;};


    bool ajouter();

    QSqlQueryModel*afficher();
        QSqlQueryModel*afficherjoin();
    QSqlQueryModel*tri();
    bool supprimer(int );
    bool modifier(int);


QSqlQueryModel *on_search_windowIconTextChangedQ();

QSqlQueryModel*rechercher(QString);

    void clear(QTableView*table);




};

#endif // CLIENT_H
