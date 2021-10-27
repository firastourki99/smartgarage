#include "voiture.h"

Voiture::Voiture()
{

}

Voiture::Voiture(int matricule, int IdClient, QString marque, QString modele, QString couleur)
{
    this->matricule = matricule;
    this->IdClient = IdClient;
    this->marque = marque;
    this->modele = modele;
    this->couleur = couleur;
}

int Voiture::getIdClient(){return IdClient;}
int Voiture::getMatricule(){return matricule;}
QString Voiture::getMarque(){return marque;}
QString Voiture::getModele(){return modele;}
QString Voiture::getCouleur(){return couleur;}


void Voiture::setIdClient(int id){this->IdClient = id;}
void Voiture::setMatricule(int matricule){this->matricule = matricule;}
void Voiture::setMarque(QString marque){this->marque = marque;}
void Voiture::setModele(QString modele){this->modele = modele;}
void Voiture::setCouleur(QString couleur){this->couleur = couleur;}

bool Voiture::ajouter()
{
    QSqlQuery query;
    QString id_string = QString::number(IdClient);
    QString id_matricule = QString::number(matricule);
          query.prepare("INSERT INTO voiture (matricule, IdClient, marque, modele, couleur) "
                        "VALUES (:IdClient, :matricule, :marque, :modele, :couleur)");
          query.bindValue(":IdClient", id_string);
          query.bindValue(":matricule", id_matricule);
          query.bindValue(":marque", marque);
          query.bindValue(":modele", modele);
          query.bindValue(":coleur", couleur);

    return query.exec();
}
