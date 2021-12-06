#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mise_a_jour_id_client();

    ui->le_modifier->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_matricule->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_recherche->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_marque->setValidator(new QRegExpValidator( QRegExp("[A-Za-z\\s]{0,12}"), this ));
    ui->le_modele->setValidator(new QRegExpValidator( QRegExp("[A-Za-z1-9\\s]{0,12}"), this ));
    //ui->le_couleur->setValidator(new QRegExpValidator( QRegExp("[A-Za-z1-9\\s]{0,12}"), this ));
    ui->le_couleur->setEnabled(false);
    ui->tab_voiture->setModel(V.afficher());
    ui->tab_voiture->setModel(V.trie());

    QPixmap buttonImage("C:/Users/mehdi/OneDrive/Bureau/Gestion_Voiture/color.png");
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
    int id = ui->cb_cin->currentText().toInt();
    QString marque = ui->le_marque->text();
    QString modele = ui->le_modele->text();
    QString couleur = ui->le_couleur->text();
    QDate date = ui->dateEdit->date();

    Voiture V(matricule, id, marque, modele, couleur, date);
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

void MainWindow::on_cb_cin_activated()
{
    mise_a_jour_id_client();

}

void MainWindow::on_pushButton_2_clicked()
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

void MainWindow::on_pb_facture_clicked()
{

}
