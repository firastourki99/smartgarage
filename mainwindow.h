#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"

#include <QMainWindow>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QSortFilterProxyModel>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void affiche();
    QSortFilterProxyModel *proxy_employe;

private slots:


    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_PDF_clicked();

    void on_modifier_clicked();

    /*void on_lineEdit_textChanged(const QString &arg1);*/

   void on_comboBox_currentIndexChanged(int index);

   void on_lineEdit_textChanged(const QString &arg1);

   void on_trier_clicked();

private:
    Ui::MainWindow *ui;
    employe e;
    employe tmp;
    employe tmprechcomp;
    int selected_employe=0;


};

#endif // MAINWINDOW_H
