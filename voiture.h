#ifndef VOITURE_H
#define VOITURE_H
#include <QSqlQuery>
#include <QString>
#include <QtDebug>
#include<QSqlQueryModel>
#include<QObject>
#include<QTableView>
#include<QDate>
class Voiture
{
public:
    Voiture();
    Voiture(int, int, QString, QString, QString, QDate);

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
    bool suprimmer(int);
    bool modifier(int);
private:
    int matricule, cin;
    QString marque, modele, couleur;
    QDate date;
};

#endif // VOITURE_H
