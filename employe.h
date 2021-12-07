#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>

#include<QTableView>
#include <QtSql/qsqltablemodel.h>
#include <QMessageBox>
#include <QtSql/QSqlError>

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
    QSqlQueryModel* afficherr();
    bool editer();
    void rechercher_emp(QTableView * table,QString);
    void clear(QTableView * table);
    //QSqlTableModel *tri1(int);
     QSqlQueryModel *tri() ;




private:
    int id;
    QString nom,prenom,email,fonction,salaire;
};

#endif // EMPLOYE_H


