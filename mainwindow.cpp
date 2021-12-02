#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"client.h"
#include<QMessageBox>
#include<QIntValidator>
#include <QPrinter>
#include<QPainter>
#include <QPdfWriter>
#include <QTextDocument>
#include <QTextStream>
#include <QPrintDialog>
#include "carte.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    carte c;
        ui->tableView_3->setModel(c.afficher());

    ui->tableView->setModel(Etmp.afficher());

    ui->lenum->setValidator(new QIntValidator(0, 9999999, this));
    ui->lecin->setValidator(new QIntValidator(0, 9999999,this));

}

void MainWindow::affiche()
{
    proxy_client = new QSortFilterProxyModel();
    proxy_client ->setSourceModel(Etmp.afficher());
    proxy_client ->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_client ->setFilterKeyColumn(selected_client);
    ui->tableView->setModel(proxy_client );

}






MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int     cin=ui->lecin->text().toInt();
    bool test=Etmp.supprimer(cin);
    if(test)
    {
        ui->tableView->setModel(Etmp.afficher());

        QMessageBox::information(nullptr,QObject::tr("Gestion Client"),QObject::tr("Client supprimé avec succées\n"
                                                                                      "click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Erreur"),QObject::tr("Suppression impossible\n"
                                                                                  "click cancel to exit."),QMessageBox::Cancel);
}



void MainWindow::on_modifier_clicked()
{
    int CIN =ui->lecin->text().toInt();
        int NUM =ui->lenum->text().toInt();

           QString NOM=ui->lenom->text();
           QString PRENOM=ui->leprenom->text();
           QString ADDRESSE=ui->lead->text();
           QString MAIL=ui->lemail->text();
           QString MATRICULE =ui->lemat->text();

           Client s(CIN,NUM,NOM,PRENOM,ADDRESSE,MAIL,MATRICULE);
         bool test=s.modifier(CIN);


         if(test)
         {
             ui->tableView->setModel(Etmp.afficher());

             QMessageBox::information(nullptr,QObject::tr("Gestion Client"),QObject::tr("Informations modifiées avec succées.\n"
                                                                                           "click cancel to exit."),QMessageBox::Cancel);
         }
         else
             QMessageBox::critical(nullptr,QObject::tr("Gestion Client"),QObject::tr("Modification impossible.\n"
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

         QMessageBox::information(nullptr,QObject::tr("Gestion Client "),QObject::tr("Client ajouté.\n"
                                                                                       "click cancel to exit."),QMessageBox::Cancel);
     }
     else
         QMessageBox::critical(nullptr,QObject::tr("Erreur"),QObject::tr("Ajout impossible.\n"
                                                                                   "click cancel to exit."),QMessageBox::Cancel);


}




void MainWindow::on_pdf_clicked()
{

      QSqlDatabase db;
                  QTableView table_client;
                  QSqlQueryModel * Modal=new  QSqlQueryModel();

                  QSqlQuery qry;
                   qry.prepare("SELECT * FROM CLIENT ");
                   qry.exec();
                   Modal->setQuery(qry);
                   table_client.setModel(Modal);


                   db.close();

                   QString strStream;
                   QTextStream out(&strStream);


                   const int rowCount = table_client.model()->rowCount();
                   const int columnCount =  table_client.model()->columnCount();

                   const QString strTitle ="Document";


                   out <<  "<html>\n"
                           "<img src='C:/Users/ASUS/Documents/kiosqueK/logocin.png' height='120' width='120'/>"
                       "<head>\n"
                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                       <<  QString("<title>%1</title>\n").arg(strTitle)
                       <<  "</head>\n"
                       "<body bgcolor=#ffffff link=#5000A0>\n"
                      << QString("<h3 style=\" font-size: 50px; font-family: Arial, Helvetica, sans-serif; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("Liste des clients")
                      <<"<br>"

                      <<"<table border=1 cellspacing=0 cellpadding=2 width=\"100%\">\n";
                   out << "<thead><tr bgcolor=#f0f0f0>";
                   for (int column = 0; column < columnCount; column++)
                       if (!table_client.isColumnHidden(column))
                           out << QString("<th>%1</th>").arg(table_client.model()->headerData(column, Qt::Horizontal).toString());
                   out << "</tr></thead>\n";

                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!table_client.isColumnHidden(column)) {
                               QString data = table_client.model()->data(table_client.model()->index(row, column)).toString().simplified();
                               out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                           }
                       }
                       out << "</tr>\n";
                   }
                   out <<  "</table>\n"
                           "<br><br>"
                           <<"<br>"
                           <<"<table border=1 cellspacing=0 cellpadding=2>\n";

                       out << "<thead><tr bgcolor=#f0f0f0>";

                           out <<  "</table>\n"

                       "</body>\n"
                       "</html>\n";

                   QTextDocument *document = new QTextDocument();
                   document->setHtml(strStream);

                   QPrinter printer;
                   QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                   if (dialog->exec() == QDialog::Accepted) {

                       document->print(&printer);
                   }

                   printer.setOutputFormat(QPrinter::PdfFormat);
                   printer.setPaperSize(QPrinter::A4);
                   printer.setOutputFileName("/tmp/client.pdf");
                   printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                   delete document;
  }






void MainWindow::on_trier_clicked()
{
    ui->tableView->setModel(Etmp.tri());
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{

    affiche();
}








void MainWindow::on_search_windowIconTextChanged(const QString &arg1)
{
    QString ch = arg1;

                    if (ch=="")
                    {
                        ui->tableView->setModel(Etmp.afficher());
                    }
                    else {
                      ui->tableView->setModel(Etmp.rechercher(ch)) ;

                    }
}








void MainWindow::on_pushButton_3_clicked()
{

     ui->tableView_2->setModel(Etmp.afficherjoin());
}

void MainWindow::on_lecin2_textChanged(const QString &arg1)
{
    QString ch = arg1;

                    if (ch=="")
                    {
                        ui->tableView->setModel(Etmp.afficher());
                    }
                    else {
                      ui->tableView->setModel(Etmp.rechercher(ch)) ;

                    }
}

void MainWindow::on_ajoutcarte_clicked()
{
    QMessageBox msgBox;

   carte c(ui->cin3->text(),ui->point->text());
       if (c.ajouter())
       {
       msgBox.setText("Ajout avec succes");
       ui->tableView_2->setModel(c.afficher());
       }
       else
       {
          msgBox.setText("Probleme d'ajout");
       }
       msgBox.exec();
}

void MainWindow::on_supprimercarte_clicked()
{ QMessageBox msgBox;
    carte c(ui->cin3->text(),ui->point->text());

        if (c.supprimer())
        {
             msgBox.setText("Suppression avec succees");
             ui->tableView_3->setModel(c.afficher());
        }
        else
            msgBox.setText("Probleme de suppresion");
        msgBox.exec();

}

void MainWindow::on_modifiercarte_clicked()
{
    QMessageBox msgBox;
    carte c(ui->cin3->text(),ui->point->text());
       if (c.update())
       {
       msgBox.setText("Mise a jour avec succes");
       ui->tableView_3->setModel(c.afficher());
       }
       else
       {
          msgBox.setText("Probleme de mise a jour");
       }
       msgBox.exec();

}

void MainWindow::on_affichercarte_clicked()
{ QMessageBox msgBox;
    carte c;
        ui->tableView_3->setModel(c.afficher());


}
