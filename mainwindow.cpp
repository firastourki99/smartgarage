#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>

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

void MainWindow::on_pushButton_clicked()
{
    int id=ui->ID->text().toInt();
    QString nom=ui->NOM->text();
    QString prenom=ui->PRENOM->text();
    QString email=ui->EMAIL->text();
    QString fonction=ui->FONCTION->text();
    QString salaire=ui->SALAIRE->text();
    employe e(id,nom,prenom,email,fonction,salaire);
    bool test=e.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout effectue\n"
                                "Click ok to exit."), QMessageBox::Ok);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("ajout non effectue\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_2_clicked()
{
    employe e1;
    e1.setid(ui->IDS->text().toInt());
    bool test =e1.supprimer(e1.getid());
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectue\n"
                                "Click Cancel to exit."), QMessageBox::Ok);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectue\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
