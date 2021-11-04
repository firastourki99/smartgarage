#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_b_ajouter_clicked()
{
    int cin=ui->le_cin->text().toInt();
    int num=ui->le_num->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString adresse=ui->le_adresse->text();
    QString voiture=ui->le_voiture->text();
    QString mail=ui->le_mail->text();
    Client C(cin,num,nom,prenom,adresse,voiture,mail);
}
