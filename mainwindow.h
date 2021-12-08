#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"client.h"
#include <QSortFilterProxyModel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
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
    Ui::MainWindow *ui;




    Client Etmp;
    int selected_client=0;




};




#endif // MAINWINDOW_H
