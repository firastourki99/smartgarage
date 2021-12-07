#include "carte.h"
#include "QMessageBox"
carte::carte()
{

}
void carte::setcin(QString x)
{
cin=x;
}
carte::carte(QString cin,QString point)
{
this->cin=cin;
this->point=point;
}

QSqlQueryModel * carte::afficher()
{

    QSqlQuery query;
    QSqlQueryModel *model=new QSqlQueryModel();
    query.prepare(QString("Select * from carte_fidelite"));
    query.exec();
    model->setQuery(query);
    return model;
}
bool carte::ajouter()
{
QSqlQuery query;
query.prepare("insert into carte_fidelite (cin,point) values (:cin,:point);");
query.bindValue(":cin",cin);
query.bindValue(":point",point);
return query.exec();
}
bool carte::update()
{

    QSqlQuery query;
    query.prepare(QString("update carte_fidelite set point=:point where cin=:cin"));
    query.bindValue(":cin",cin);
    query.bindValue(":point",point);
    return query.exec();

}
bool carte::supprimer()
{
    QSqlQuery query;
    query.prepare(QString("DELETE from carte_fidelite where cin=:cin"));
    query.bindValue(":cin",cin);
    return query.exec();
}
QString  carte::recherchee()
{
    QSqlQuery query;
    query.prepare(QString("select cin from carte_fidelite where cin=:cin"));
    query.bindValue(0,cin);
    query.exec();
    query.next();
    return query.value(0).toString();


}
