#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QFileDialog>
#include <QTextStream>
#include <QFileDialog>
#include <QTextDocument>
#include <QSqlQuery>
#include <QPieSeries>
#include <QtCharts>
#include <QChart>






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ID->setValidator( new QIntValidator(100,9999999,this));
    ui->tab_employe->setModel(e.afficher());
    ui->comboBox_fonction->setModel(e.afficherr());


    affiche();



}
void MainWindow::affiche()
{
    proxy_employe = new QSortFilterProxyModel();
    proxy_employe ->setSourceModel(e.afficher());
    proxy_employe ->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_employe ->setFilterKeyColumn(selected_employe);
    ui->tab_employe->setModel(proxy_employe );


}








MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_ajouter_clicked()
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

void MainWindow::on_modifier_clicked()
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



void MainWindow::on_trier_clicked()
{

    ui->tab_employe->setModel(e.tri());

}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{

}



void MainWindow::on_pushButton_clicked()
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
        qDebug() <<v;
        qDebug() <<d;
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

void MainWindow::on_comboBox_fonction_activated(const QString &arg1)
{


}

void MainWindow::on_pushButton_2_clicked()
{

}
