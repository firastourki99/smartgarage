#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"client.h"
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int     cin=ui->lecin2->text().toInt();
    bool test=Etmp.supprimer(cin);
    if(test)
    {
        ui->tableView->setModel(Etmp.afficher());

        QMessageBox::information(nullptr,QObject::tr("database is open "),QObject::tr("connection successful.\n"
                                                                                      "click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("data is not open"),QObject::tr("connection failed.\n"
                                                                                  "click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_modifier_clicked()
{
    int CIN =ui->lecin1->text().toInt();
        int NUM =ui->lenum1->text().toInt();

           QString NOM=ui->lenom1->text();
           QString PRENOM=ui->leprenom1->text();
           QString ADDRESSE=ui->lead1->text();
           QString MAIL=ui->lemail1->text();
           QString MATRICULE =ui->lemat1->text();

           Client s(CIN,NUM,NOM,PRENOM,ADDRESSE,MAIL,MATRICULE);
         bool test=s.modifier(CIN);


         if(test)
         {
             ui->tableView->setModel(Etmp.afficher());

             QMessageBox::information(nullptr,QObject::tr("database is open "),QObject::tr("connection successful.\n"
                                                                                           "click cancel to exit."),QMessageBox::Cancel);
         }
         else
             QMessageBox::critical(nullptr,QObject::tr("data is not open"),QObject::tr("connection failed.\n"
                                                                                       "click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_ajouter_clicked()
{
    int CIN =ui->lecin->text().toInt();
    int NUM =ui->lenum->text().toInt();

       QString NOM=ui->lenom->text();
       QString PRENOM=ui->leprenom->text();
       QString ADDRESSE=ui->lead->text();
       QString MAIL=ui->lemail->text();
       QString MATRICULE =ui->lemat->text();

       Client a(CIN,NUM,NOM,PRENOM,ADDRESSE,MAIL,MATRICULE);
     bool test=a.ajouter();


     if(test)
     {
         ui->tableView->setModel(Etmp.afficher());

         QMessageBox::information(nullptr,QObject::tr("database is open "),QObject::tr("connection successful.\n"
                                                                                       "click cancel to exit."),QMessageBox::Cancel);
     }
     else
         QMessageBox::critical(nullptr,QObject::tr("data is not open"),QObject::tr("connection failed.\n"
                                                                                   "click cancel to exit."),QMessageBox::Cancel);
}
