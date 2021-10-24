#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include<QSqlQueryModel>

class employe
{
public:
    employe ();
    employe(int,QString,QString,QString,QString,QString);
    int getid();
    QString getnom();
    QString getprenom();
    QString getemail();
    QString getfonction();
    QString getsalaire();
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setemail(QString);
    void setfonction(QString);
    void setsalaire(QString);
    bool ajouter();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    bool editer();


private:
    int id;
    QString nom,prenom,email,fonction,salaire;
};

#endif // EMPLOYE_H
