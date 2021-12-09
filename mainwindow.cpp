#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QIntValidator>
#include <QFileDialog>
#include <QTextStream>
#include <QFileDialog>
#include <QTextDocument>
#include <QtSql/QSqlQuery>
#include <QtCharts/QPieSeries>
#include <QtCharts/QtCharts>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controleSaisie();
    QDateTime UTC(QDateTime::currentDateTimeUtc());
     QDateTime local(UTC.toLocalTime());
              qDebug() << "UTC time is:" << UTC;
              qDebug() << "Local time is:" << local;
             // qDebug() << "No difference between times:" << UTC.secsTo(local);
              ui->dateTimeEdit->setDateTime(local);
              ui->tableService->setModel(sr.afficher());
    ui->stackedWidget->setCurrentIndex(0);
    //QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
    ui->ID->setValidator( new QIntValidator(100,9999999,this));
    ui->tab_employe->setModel(e.afficher());
    ui->comboBox_fonction->setModel(e.afficherr());

    ui->tableView_3->setModel(c.afficher());

    ui->tableView->setModel(Etmp.afficher());

    ui->lenum->setValidator(new QIntValidator(0, 9999999, this));
    ui->lecin->setValidator(new QIntValidator(0, 9999999,this));

    affiche();
    mise_a_jour_id_client();
    //connect(ui->cb_cin, SIGNAL(currentIndexChanged(const QString)), ui->cb_cin, SLOT(mise_a_jour_id_client()));


    ui->le_modifier->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_arduino->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_matricule->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_recherche->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_marque->setValidator(new QRegExpValidator( QRegExp("[A-Za-z\\s]{0,12}"), this ));
    ui->le_modele->setValidator(new QRegExpValidator( QRegExp("[A-Za-z1-9\\s]{0,12}"), this ));
    //ui->le_couleur->setValidator(new QRegExpValidator( QRegExp("[A-Za-z1-9\\s]{0,12}"), this ));
    ui->le_couleur->setEnabled(false);
    ui->tab_voiture->setModel(V.afficher());
    ui->tab_voiture->setModel(V.trie());
    ui->tab_voiture_ard->setModel(V.afficher());
    ui->tab_voiture_ard->setModel(V.trie());

    QPixmap buttonImage("C:/Users/mehdi/OneDrive/Bureau/Gestion_Voiture/color.png");
    QIcon buttonIcon(buttonImage);
    ui->pb_color->setIcon(buttonImage);
    ui->pb_color->setIconSize(QSize(50,30));
    QPixmap pix("C:/Users/mehdi/OneDrive/Bureau/Gestion_Voiture/recherche.png");
    int w = ui->icon_label->width();
    int h = ui->icon_label->height();
    ui->icon_label->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));


}
void MainWindow::affiche()
{
    proxy_employe = new QSortFilterProxyModel();
    proxy_employe ->setSourceModel(e.afficher());
    proxy_employe ->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_employe ->setFilterKeyColumn(selected_employe);
    ui->tab_employe->setModel(proxy_employe );
}


//void MainWindow::update_label()
//{
//    data = A.read_from_arduino();
//    if (data == "1")
//    {
//        data.clear();
//        ui->lb_ard->setText("Carte non valide");
//    }
//    else if (data == "2")
//    {
//        data.clear();
//        ui->lb_ard->setText("Carte valide");
//    }
//}





MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pb_ajouter_emp_clicked()
{
    int id=ui->ID->text().toInt();
    QString nom=ui->NOM->text();
    QString prenom=ui->PRENOM->text();
    QString email=ui->EMAIL->text();
    QString fonction=ui->comboBox_fonction->currentText();
    QString salaire=ui->SALAIRE->text();
    employe e(id,nom,prenom,email,fonction,salaire);
    bool test=e.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout effectue\n"
                                "Click ok to exit."), QMessageBox::Ok);
        ui->tab_employe->setModel(e.afficher());
        ui->comboBox_fonction->setModel(e.afficherr());

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("ajout non effectue\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_supprimer_clicked()
{
    employe e1;
    e1.setid(ui->IDS->text().toInt());
    bool test =e1.supprimer(e1.getid());
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectue\n"
                                "Click Cancel to exit."), QMessageBox::Ok);
        ui->tab_employe->setModel(e.afficher());
        ui->comboBox_fonction->setModel(e.afficherr());

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectue\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_PDF_clicked()
{
    QString strStream;
                          QTextStream out(&strStream); //eureur

                            const int rowCount = ui->tab_employe->model()->rowCount();
                            const int columnCount = ui->tab_employe->model()->columnCount();

                            out <<  "<html>\n"
                                "<head>\n"
                                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                <<  QString("<title>%1</title>\n").arg("strTitle")
                                <<  "</head>\n"
                                "<body bgcolor=#ffffff link=#5000A0>\n"

                               //     "<align='right'> " << datefich << "</align>"
                                "<center> <H1>Liste des employes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                            // headers
                            out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                            for (int column = 0; column < columnCount; column++)
                                if (!ui->tab_employe->isColumnHidden(column))
                                    out << QString("<th>%1</th>").arg(ui->tab_employe->model()->headerData(column, Qt::Horizontal).toString());
                            out << "</tr></thead>\n";

                            // data table
                            for (int row = 0; row < rowCount; row++) {
                                out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                for (int column = 0 ; column < columnCount; column++) {
                                    if (!ui->tab_employe->isColumnHidden(column)) {
                                        QString data = ui->tab_employe->model()->data(ui->tab_employe->model()->index(row, column)).toString().simplified();
                                        out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                    }
                                }
                                out << "</tr>\n";
                            }
                            out <<  "</table> </center>\n"
                                "</body>\n"
                                "</html>\n";

                      QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                        if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                       QPrinter printer (QPrinter::PrinterResolution);
                        printer.setOutputFormat(QPrinter::PdfFormat);
                       printer.setPaperSize(QPrinter::A4);
                      printer.setOutputFileName(fileName);

                       QTextDocument  doc;
                        doc.setHtml(strStream);
                        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                        doc.print(&printer);
}

void MainWindow::on_pb_modifier_emp_clicked()
{
    int id =ui->ID->text().toInt();

        QString nom=ui->NOM->text();
        QString prenom=ui->PRENOM->text();
        QString email=ui->EMAIL->text();
        QString fonction=ui->comboBox_fonction->currentText();
        QString salaire=ui->SALAIRE->text();


        employe e(id,nom,prenom,email,fonction,salaire);

        bool test=e.editer();

        if(test){


    QMessageBox::information(nullptr, QObject::tr("edité un employe"),
                        QObject::tr("employe edité.\n"
                                    "Click Ok to exit."), QMessageBox::Ok);
    ui->tab_employe->setModel(e.afficher());
    ui->comboBox_fonction->setModel(e.afficherr());


    }
        else{
            QMessageBox::critical(nullptr, QObject::tr("editer un employe"),
                        QObject::tr("employe non edité.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);


     }
}


//recherche avec combobox
void MainWindow::on_comboBox_currentIndexChanged(int index)
{

        selected_employe=ui->comboBox->currentIndex();
        affiche();

}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    proxy_employe->setFilterFixedString(arg1);
}



void MainWindow::on_trier_emp_clicked()
{

    ui->tab_employe->setModel(e.tri());

}





void MainWindow::on_pb_email_clicked()
{

    dialog_email = new Dialog_email(this);
    dialog_email->show();

}





void MainWindow::on_stat_clicked()
{

    QSqlQuery query ;
        query.exec("SELECT fonction FROM employe");
        int v = 0;
        int d = 0;
        while(query.next())
        {
            if (query.value(0) == "vidange")
            {
                v ++;
            }
            else if(query.value(0) == "diagnostic")
            {
                d ++;
            }
        }
        float total = d + v;
        float t = d /total;
        float f = v /total;
        QPieSeries *series = new QPieSeries();
        series->setHoleSize(0.35);//Set the size of the inner hole of the ring [0-1]
        series->append("diagnostic",t);//Add a block for repaired cars
        series->append("vidange", f);//Add a block for non repaired cars
        QPieSlice *slice0 = series->slices().at(0);//Add a slice, accounting for 30%, and instantiate a QPieSlice to point to the slice
        slice0->setExploded(true);//Let the arc block separate from the main ring
        slice0->setLabelVisible(true);//Display the label of the arc block
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setExploded(true);
        slice1->setLabelVisible(true);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Les services des employes");
        chart->setTheme(QChart::ChartThemeLight);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->legend()->setFont(QFont("Arial", 7));
        //chart->legend()->hide();

        QChartView *chartView = new QChartView(chart);//Instantiate QChartView control
        chartView->setRenderHint(QPainter::Antialiasing);//Set prompt (QPainter::Antialiasing eliminates aliasing)
        chartView->resize(800,600);
        chartView->show();
}



void MainWindow::affiche2()
{
    proxy_client = new QSortFilterProxyModel();
    proxy_client ->setSourceModel(Etmp.afficher());
    proxy_client ->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_client ->setFilterKeyColumn(selected_client);
    ui->tableView->setModel(proxy_client);

}




void MainWindow::on_pb_supp_client_clicked()
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



void MainWindow::on_modifier2_clicked()
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

void MainWindow::on_ajouter2_clicked()
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






void MainWindow::on_trier_client_clicked()
{
    ui->tableView->setModel(Etmp.tri());
}

//void MainWindow::on_comboBox2_currentIndexChanged(int index)
//{
//    affiche2();
//}








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



void MainWindow::on_lecin2_textEdited(const QString &arg1)
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


void MainWindow::on_pb_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pb_client_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pb_retour_client_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pb_retour_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    d->close_arduino();
}




void MainWindow::on_pb_ajouter_clicked()
{
    int matricule = ui->le_matricule->text().toInt();
    int id = ui->cb_cin->currentText().toInt();
    QString marque = ui->le_marque->text();
    QString modele = ui->le_modele->text();
    QString couleur = ui->le_couleur->text();
    QDate date = ui->dateEdit->date();
    int etat = ui->cb_etat->currentText().toInt();

    Voiture V(matricule, id, marque, modele, couleur, date, etat);
    bool test = V.ajouter();

    if(test)
    {
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

    if ((*s) == "ID") (*a) = ui->cb_cin->currentText();
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


void MainWindow::on_pb_pdf_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tab_voiture->model()->rowCount();
    const int columnCount = ui->tab_voiture->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("Voitures")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tab_voiture->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tab_voiture->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tab_voiture->isColumnHidden(column)) {
                QString data = ui->tab_voiture->model()->data(ui->tab_voiture->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
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

    delete document;
}


void MainWindow::mise_a_jour_id_client()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery();
    qry->prepare("SELECT cin from client");
    qry->exec();
    model->setQuery(*qry);
    ui->cb_cin->setModel(model);
}


void MainWindow::on_pb_stat_v_clicked()
{
    QSqlQuery query ;
    query.exec("SELECT etat FROM voiture");
    int etat_t = 0;
    int etat_f = 0;
    while(query.next())
    {
        if (query.value(0) == 1)
        {
            etat_t ++;
        }
        else if(query.value(0) == 0)
        {
            etat_f ++;
        }
    }
    float total = etat_t + etat_f;
    float t = etat_t /total;
    float f = etat_f /total;
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);//Set the size of the inner hole of the ring [0-1]
    series->append("Réparées",t);//Add a block for repaired cars
    series->append("Non réparées", f);//Add a block for non repaired cars
    QPieSlice *slice0 = series->slices().at(0);//Add a slice, accounting for 30%, and instantiate a QPieSlice to point to the slice
    slice0->setExploded(true);//Let the arc block separate from the main ring
    slice0->setLabelVisible(true);//Display the label of the arc block
    QPieSlice *slice1 = series->slices().at(1);
    slice1->setExploded(true);
    slice1->setLabelVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Les etats des voitures");
    chart->setTheme(QChart::ChartThemeLight);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setFont(QFont("Arial", 7));
    //chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);//Instantiate QChartView control
    chartView->setRenderHint(QPainter::Antialiasing);//Set prompt (QPainter::Antialiasing eliminates aliasing)
    chartView->resize(800,600);
    chartView->show();

}

void MainWindow::on_pb_retour_v_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pb_voiture_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pb_arduino_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pb_ard_clicked()
{
    int ret=A.connect_arduino();
    switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                break;
          case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
               break;
         case(-1):qDebug() << "arduino is not available";
           }
    QString s = ui->le_arduino->text();
    qDebug()<<s;
    if (s == "Carte valide")
    {
        QSqlQuery q("select etat from voiture where matricule =:mat");
        q.bindValue(":mat", s);
        qDebug()<<q.first();
            int etat = q.value(0).toInt();
            qDebug()<<etat;

            if (etat == 0)
            {
                A.write_to_arduino("0");
            }
            else if(etat == 1)
            {
                A.write_to_arduino("1");
            }

    }
    else
    {
        A.write_to_arduino("2");
        //QMessageBox::critical(nullptr,QObject::tr("Erreur"),QObject::tr("Ajout impossible.\n""Veuillez inserer un carte valide."),QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_retour_ard_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_pushButton_7_clicked()
{
    d = new Dialog(this);
    d->show();

}


//******************************************

void MainWindow::controleSaisie(){
     ui->tableService->setModel(sr.afficher());
     ui->s_id->clear();
     ui->s_nom->clear();
     ui->s_cout->clear();
     ui->s_duree->clear();
     ui->stackedWidget->setCurrentIndex(0);
   //  ui->s_id_modifier->setEnabled(false);
     ui->s_nom_modifier->clear();
     ui->s_cout_modifier->clear();
     ui->s_duree_modifier->clear();
     ui->s_nom_modifier->hide();
     ui->s_cout_modifier->hide();
     ui->s_duree_modifier->hide();
     ui->s_dis_e->hide();
     ui->service_modifier->hide();
     ui->service_supprimer->hide();
     ui->s_id->setValidator(new QIntValidator(0,9999999,this));
     ui->s_nom->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
     ui->s_nom_modifier->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
     ui->s_cout->setValidator(new QIntValidator(0,9999999,this));
     ui->s_cout_modifier->setValidator(new QIntValidator(0,9999999,this));
     ui->s_id_modifier->setValidator(new QIntValidator(0,9999999,this));


}

void MainWindow::on_ajoutFormulaire_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
}

void MainWindow::on_button_Ajouter_clicked()
{
    int id = ui->s_id->text().toInt();
    QString nom = ui->s_nom->text();
    int cout = ui->s_cout->text().toInt();
    int duree = ui->s_duree->text().toInt();
    QString disponibilite = ui->s_dis->currentText();
    if (id<=0){
        QMessageBox::critical(nullptr, QObject::tr("Ajout service"),
                                      QObject::tr("Verifier le champ id!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(nom.size()<=2){
        QMessageBox::critical(nullptr, QObject::tr("Produit ajout"),
                                      QObject::tr("Saisir un nom > 3 charachters!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(cout<=0){
        QMessageBox::critical(nullptr, QObject::tr("Service ajout"),
                                      QObject::tr("Le prix ne doit pas etre 0 Ou negative .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(duree<=3){
        QMessageBox::critical(nullptr, QObject::tr("Service ajout"),
                                      QObject::tr("Saisir une duree valide .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(disponibilite.size()<=3){
            QMessageBox::critical(nullptr, QObject::tr("Service ajout"),
                                          QObject::tr("Choir une etat valide .\n"
                                                      "Click Ok to exit."), QMessageBox::Ok);

}
    else{
    service sd(id,nom,cout,duree,disponibilite);
    bool test = sd.ajouter();
    if (test){
        controleSaisie();
        QMessageBox::information(nullptr, QObject::tr("Service ajout"),
                                      QObject::tr("Success !! .\n"
                                                  "Cli"
                                                  "*ck Ok to exit."), QMessageBox::Ok);
        Notifications *notif=new Notifications();
        notif->show_notif("succes","Service Ajouter");
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Service ajout"),
                                      QObject::tr("ID deja utiliser ! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    }
}

void MainWindow::on_tableService_activated(const QModelIndex &index)
{
    QString val=ui->tableService->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("Select nom,cout,duree from service where  id='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {
                        ui->s_id_modifier->setText(val);
                        ui->s_nom_modifier->setText(qry.value(0).toString());
                        ui->s_cout_modifier->setText(qry.value(1).toString());
                        ui->s_duree_modifier->setText(qry.value(2).toString());

                        ui->s_id_modifier->setEnabled(false);
                        ui->s_nom_modifier->show();
                        ui->s_cout_modifier->show();
                        ui->s_duree_modifier->show();
                        ui->s_dis_e->show();
                        ui->service_modifier->show();
                        ui->service_supprimer->show();
                    }
        }
}

void MainWindow::on_service_supprimer_clicked()
{
    int id=ui->s_id_modifier->text().toInt();

    bool test2=sr.supprimer(id);
    if(test2){
        controleSaisie();
        QMessageBox::information(nullptr, QObject::tr("Service Supprimer"),
                                      QObject::tr("Succés .\n" "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        controleSaisie();
        QMessageBox::critical(nullptr, QObject::tr("Service Supprimer"),
                                      QObject::tr("Eurreur !! !\n"), QMessageBox::Cancel);

    }
}

void MainWindow::on_service_modifier_clicked()
{
    int id = ui->s_id_modifier->text().toInt();
    QString nom = ui->s_nom_modifier->text();
    int cout = ui->s_cout_modifier->text().toInt();
    int duree = ui->s_duree_modifier->text().toInt();
    QString disponibilite = ui->s_dis_e->currentText();
    if (id<=0){
        QMessageBox::critical(nullptr, QObject::tr("Modifier service"),
                                      QObject::tr("Verifier le champ id!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(nom.size()<=2){
        QMessageBox::critical(nullptr, QObject::tr("Modifier ajout"),
                                      QObject::tr("Saisir un nom > 3 charachters!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(cout<=0){
        QMessageBox::critical(nullptr, QObject::tr("Modifier ajout"),
                                      QObject::tr("Le prix ne doit pas etre 0 Ou negative .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(duree<=3){
        QMessageBox::critical(nullptr, QObject::tr("Modifier ajout"),
                                      QObject::tr("Saisir une duree valide .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(disponibilite.size()<=3){
            QMessageBox::critical(nullptr, QObject::tr("Modifier ajout"),
                                          QObject::tr("Choir une etat valide .\n"
                                                      "Click Ok to exit."), QMessageBox::Ok);

}
    else{
    service sd(id,nom,cout,duree,disponibilite);
    bool test = sd.modifier(id);
    if (test){
        controleSaisie();
        QMessageBox::information(nullptr, QObject::tr("Modifier ajout"),
                                      QObject::tr("Success !! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Modifier ajout"),
                                      QObject::tr("ID deja utiliser ! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    }
}

void MainWindow::on_s_recherche_textChanged(const QString &arg1)
{
     ui->tableService->setModel(sr.afficherRech(arg1));
}



void MainWindow::on_pushButton_clicked()
{
   s = new stat_combo();

  s->setWindowTitle("statistique Services");
  s->choix_bar();
  s->show();


}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
    ui->s_nom_modifier->show();
    ui->s_cout_modifier->show();
    ui->s_duree_modifier->show();
    ui->s_dis_e->show();
    ui->s_id_modifier->show();
    ui->service_modifier->show();
    ui->service_supprimer->show();
}

void MainWindow::on_envoie_mailservice_clicked()
{
    mailing_sercice m;
    m.exec();

}

void MainWindow::on_pb_gc_service_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pb_retour_service_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
