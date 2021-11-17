#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog2.h"
#include "voiture.h"
#include <QIntValidator>
#include <QColor>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_modifier->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_matricule->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_marque->setValidator(new QRegExpValidator( QRegExp("[A-Za-z\\s]{0,12}"), this ));
    ui->le_modele->setValidator(new QRegExpValidator( QRegExp("[A-Za-z1-9\\s]{0,12}"), this ));
    ui->le_couleur->setValidator(new QRegExpValidator( QRegExp("[A-Za-z\\s]{0,12}"), this ));
    ui->le_couleur->setEnabled(false);
    ui->tab_voiture->setModel(V.afficher());
    ui->tab_voiture->setModel(V.trie());

    QPixmap buttonImage("C:/Users/mehdi/OneDrive/Bureau/Gestion_Voiture/color.jpg");
    QIcon buttonIcon(buttonImage);
    ui->pb_color->setIcon(buttonImage);
    ui->pb_color->setIconSize(QSize(50,30));
    QPixmap pix("C:/Users/mehdi/OneDrive/Bureau/Gestion_Voiture/recherche.png");
    int w = ui->icon_label->width();
    int h = ui->icon_label->height();
    ui->icon_label->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;
}



QString MainWindow::hexcolor(int r, int g, int b)
{
    return (QString) ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
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
        ui->le_id->clear();
        ui->le_marque->clear();
        ui->le_matricule->clear();
        ui->le_couleur->clear();
        ui->le_modele->clear();
        ui->dateEdit->clear();
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
    V1.setIdClient(ui->le_modifier->text().toInt());
    bool test = V1.suprimmer(V1.getIdClient());
    if(test)
    {
        ui->le_modifier->clear();
        ui->tab_voiture->setModel(V.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Suppression avec succes!\n"
                                "Click Ok to exit."), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("Echec de suppression.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
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
        ui->le_modifier->clear();
        ui->tab_voiture->setModel(V.afficher());
        msgBox.setText("Modification avec succes!");
    }
    else
    {
        msgBox.setText("Echec de modification");
    }
    msgBox.exec();
}

void MainWindow::on_pb_color_clicked()
{
    Dialog2 dialog;
    dialog.setModal(true);
    dialog.exec();
    ui->le_couleur->setText(dialog.getRefColor());
}



void MainWindow::on_CB_trie_currentIndexChanged(const QString &text)
{
    if (text == "matricule") ui->tab_voiture->setModel(V.trie());
    else if (text == "ID") ui->tab_voiture->setModel(V.trie2());
    else ui->tab_voiture->setModel(V.trie3());
}

void MainWindow::on_le_recherche_textEdited(const QString &text)
{
    ui->tab_voiture->setModel(V.recherche(text));
}
