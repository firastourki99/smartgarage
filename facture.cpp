#include "facture.h"
#include "ui_facture.h"

facture::facture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::facture)
{
    ui->setupUi(this);
}

facture::~facture()
{
    delete ui;
}

void facture::on_pb_facture2_clicked()
{
    QSqlQuery q ;
    q.exec("SELECT matricule,nom_service FROM recevoir");
    float prix = 0;
    while(q.next())
    {
        int mat = q.value(0).toInt();
        if (mat == ui->le_facture->text())
        {
            QString serv = q.value(1).toString();
            QSqlQuery query;
            query.exec("SELECT cout from service where nom =:nom");
            query.bindValue(":nom",serv);
            prix += query.exec();
        }
    }
}
// bool facture::ajouter(float prix)
// {

//    QSqlQuery query;
//          query.prepare("INSERT INTO facture (num, CIN, marque, modele, couleur, DATE_AJOUT)"
//                        "VALUES (:matricule, :IdClient, :marque, :modele, :couleur, :date)");
//        query.bindValue(":IdClient", id_string);

//     return query.exec();
// }




