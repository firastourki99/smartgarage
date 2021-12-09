#ifndef SERVICE_H
#define SERVICE_H
#include <QSqlQueryModel>
#include <QString>


class service
{
public:
    service();
    service(int,QString,int,int,QString);
    int getId(){return id;}
    QString getNom(){return nom;}
     int getDuree(){return duree;}
      QString getDisponibilite(){return disponibilite;}
    int getCout(){return cout;}
    bool ajouter();
    bool modifier(int);
    bool supprimer(int);
    QSqlQueryModel * afficher();
    QSqlQueryModel *afficherRech(QString res);
   QString  apercu_pdf();
     QSqlQueryModel *  trier_nom();
    void  showTime();




private:
    int id,cout,duree;
    QString nom,disponibilite;
};
#endif // SERVICE_H
