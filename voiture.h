#ifndef VOITURE_H
#define VOITURE_H
#include <QSqlQuery>
#include <QString>
#include <QtDebug>
#include<QSqlQueryModel>
#include<QObject>
#include<QTableView>
class Voiture
{
public:
    Voiture();
    Voiture(int, int, QString, QString, QString);

    //GETTERS
    int getIdClient();
    int getMatricule();
    QString getMarque();
    QString getModele();
    QString getCouleur();

    //SETTERS
    void setIdClient(int);
    void setMatricule(int);
    void setMarque(QString);
    void setModele(QString);
    void setCouleur(QString);

    //functions
    bool ajouter();
    QSqlQueryModel * afficher();
    bool suprimmer(int);
private:
    int matricule, IdClient;
    QString marque, modele, couleur;
};

#endif // VOITURE_H
