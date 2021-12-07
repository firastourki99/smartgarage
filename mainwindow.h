#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include "client.h"
#include "carte.h"
#include "voiture.h"
#include "dialog_email.h"
#include "dialog2.h"
#include <QColor>
#include <QMainWindow>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QSortFilterProxyModel>
#include <QIntValidator>





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSortFilterProxyModel *proxy_client;

    QSortFilterProxyModel *proxy_employe;
    void afficher();
    void affiche();
    void tri();



private slots:

    void on_pb_email_clicked();

    void on_pb_modifier_emp_clicked();

    void on_pb_ajouter_emp_clicked();

    void on_pdf_clicked();


    void on_trier_emp_clicked();


    void affiche2();

    void on_comboBox_currentIndexChanged(int index);


    void on_search_windowIconTextChanged(const QString &iconText);

    //void on_search_clicked();

    void on_lecin2_textChanged(const QString &arg1);


    void on_pushButton_3_clicked();

    //void on_pushButton_4_clicked();

    void on_ajoutcarte_clicked();

    void on_supprimercarte_clicked();

    void on_modifiercarte_clicked();

    void on_affichercarte_clicked();

    //void on_pushButton_2_clicked();

    void on_lecin2_textEdited(const QString &arg1);

    void on_ajouter2_clicked();

    void on_supprimer_clicked();

    void on_PDF_clicked();

    void on_modifier2_clicked();

    /*void on_lineEdit_textChanged(const QString &arg1);*/

   //void on_comboBox2_currentIndexChanged(int index);

   void on_lineEdit_textChanged(const QString &arg1);

   void on_trier_client_clicked();

   //void on_pushButton2_clicked();

   void on_stat_clicked();

   //void on_comboBox_fonction_activated(const QString &arg1);

   void on_pb_supp_client_clicked();

   void on_pb_employe_clicked();

   void on_pb_client_clicked();

   void on_pb_retour_client_clicked();

   void on_pb_retour_employe_clicked();


   //********************************************************************//

   void on_pb_ajouter_clicked();

   void on_pb_supprimer_clicked();

   void on_pb_modifier_clicked();

   void on_pb_color_clicked();

   void on_CB_trie_currentIndexChanged(const QString &);

   void on_le_recherche_textEdited(const QString &arg1);

   void on_pb_pdf_clicked();

   void mise_a_jour_id_client();

   void on_pb_stat_v_clicked();

   void on_pb_retour_v_clicked();

   void on_pb_voiture_clicked();

private:

    Ui::MainWindow *ui;
    Dialog_email *dialog_email;
    employe e;
    Client Etmp;
    carte c;
    Voiture V;

    int selected_client=0;
    int selected_employe=0;
};

#endif // MAINWINDOW_H
