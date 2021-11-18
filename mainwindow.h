#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include "dialog_email.h"
#include "dialog_stat.h"
#include <QMainWindow>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QSortFilterProxyModel>
#include <QSqlError>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSortFilterProxyModel *proxy_employe;
    void afficher();
    void affiche();
    void tri();



private slots:


    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_PDF_clicked();

    void on_modifier_clicked();

    /*void on_lineEdit_textChanged(const QString &arg1);*/

   void on_comboBox_currentIndexChanged(int index);

   void on_lineEdit_textChanged(const QString &arg1);





   void on_trier_clicked();

   void on_comboBox_2_currentIndexChanged(int index);


   void on_pushButton_clicked();
   void on_stat_clicked();

private:
    Ui::MainWindow *ui;
    Dialog_email *dialog_email;
    Dialog_stat *dialog_stat;
    employe e;



    int selected_employe=0;


};

#endif // MAINWINDOW_H
