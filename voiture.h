#ifndef VOITURE_H
#define VOITURE_H
#include <QSqlQuery>
#include <QString>
#include <QtDebug>
#include<QSqlQueryModel>
#include<QObject>
#include<QTableView>
#include<QDate>
#include<QMessageBox>
class Voiture
{
public:
    Voiture();
    Voiture(int, int, QString, QString, QString, QDate, int);

    //GETTERS
    int getIdClient();
    int getMatricule();
    QString getMarque();
    QString getModele();
    QString getCouleur();
    QDate getDate();

    //SETTERS
    void setIdClient(int);
    void setMatricule(int);
    void setMarque(QString);
    void setModele(QString);
    void setCouleur(QString);
    void setDate(QDate);

    //functions
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * recherche(QString);
    QSqlQueryModel * trie();
    QSqlQueryModel * trie2();
    QSqlQueryModel * trie3();
    bool suprimmer(int);
    bool modifier(int&, QString&, QString&);
private:
    int matricule, cin, etat;
    QString marque, modele, couleur;
    QDate date;
};

#endif // VOITURE_H
