#ifndef FIRAS_H
#define FIRAS_H

#include <QMainWindow>
#include"client.h"
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class firas; }
QT_END_NAMESPACE

class firas : public QMainWindow
{
    Q_OBJECT

public:
    firas(QWidget *parent = nullptr);
    ~firas();
    QSortFilterProxyModel *proxy_client;

private slots:
    void on_pushButton_clicked();

    void on_modifier_clicked();

    void on_ajouter_clicked();

    void on_pdf_clicked();


    void on_trier_clicked();


    void affiche();

    void on_comboBox_currentIndexChanged(int index);


    void on_search_windowIconTextChanged(const QString &iconText);

    void on_search_clicked();

    void on_lecin2_textChanged(const QString &arg1);


    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_ajoutcarte_clicked();

    void on_supprimercarte_clicked();

    void on_modifiercarte_clicked();

    void on_affichercarte_clicked();

    void on_pushButton_2_clicked();

    void on_lecin2_textEdited(const QString &arg1);

private:
    Ui::firas *ui;




    Client Etmp;
    int selected_client=0;




};




#endif // MAINWINDOW_H
