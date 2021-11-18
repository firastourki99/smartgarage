#ifndef CARTE_H
#define CARTE_H
#include <QString>
#include <QSqlQueryModel>

class carte
{
public:
    carte();


    void carte::setid(QString );

    QSqlQueryModel * carte::afficher();
    bool carte::ajouter();
    bool carte::update();
    bool carte::supprimer();
    QString  carte::recherche();
};

#endif // CARTE_H
