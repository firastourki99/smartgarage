#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "voiture.h"
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_matricule->setValidator(new QIntValidator(0, 9999999, this));
    ui->tab_voiture->setModel(V.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pb_ajouter_clicked()
{
    int matricule = ui->le_matricule->text().toInt();
    int id = ui->le_id->text().toInt();
    QString marque = ui->le_marque->text();
    QString modele = ui->le_modele->text();
    QString couleur = ui->le_couleur->text();
    QDate date = ui->dateEdit->date();

    Voiture V(matricule, id, marque, modele, couleur, date);
    bool test = V.ajouter();

    if(test)
    {
        ui->tab_voiture->setModel(V.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Ok to exit."), QMessageBox::Ok);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("Ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pb_supprimer_clicked()
{

    Voiture V1;
    V1.setIdClient(ui->le_supprimer->text().toInt());
    bool test = V1.suprimmer(V1.getIdClient());
    QMessageBox msgBox;
    if(test)
    {
        ui->tab_voiture->setModel(V.afficher());
        msgBox.setText("Suppression avec succes!");
    }
    else
    {
        msgBox.setText("Echec de suppression");
    }
    msgBox.exec();
}

void MainWindow::on_pb_modifier_clicked()
{
    Voiture V1;
    QString *a = new QString("");
    QString *s = new QString(ui->CB_modify->currentText());
    int row =ui->le_modifier->text().toInt();
    int *b = &row;

    if ((*s) == "ID") (*a) = ui->le_id->text();
    else if ((*s) == "Marque") (*a) = ui->le_marque->text();
    else if ((*s) == "Modele") (*a) = ui->le_modele->text();
    else if ((*s) == "Couleur") (*a) = ui->le_couleur->text();
    bool test = V1.modifier((*b), (*s), (*a));

    QMessageBox msgBox;
    if(test)
    {
        ui->tab_voiture->setModel(V.afficher());
        msgBox.setText("Modification avec succes!");
    }
    else
    {
        msgBox.setText("Echec de modification");
    }
    msgBox.exec();
}
