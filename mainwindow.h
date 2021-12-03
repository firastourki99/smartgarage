#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>
#include "dialog2.h"
#include "voiture.h"
#include <QIntValidator>
#include <QColor>
#include <QtCharts>
#include <QChart>
#include <QPieSeries>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QPrintDialog>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include "voiture.h"

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_color_clicked();

    QString hexcolor(int r, int g, int b);

    void on_CB_trie_currentIndexChanged(const QString &);

    void on_le_recherche_textEdited(const QString &arg1);

    void on_pb_pdf_clicked();

    void mise_a_jour_id_client();


    void on_cb_cin_activated();

    void on_pushButton_2_clicked();

    void on_pb_facture_clicked();

private:
    Ui::MainWindow *ui;
    Voiture V;

};

#endif // MAINWINDOW_H
