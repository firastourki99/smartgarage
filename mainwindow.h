#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"

#include <QMainWindow>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void afficher1();

private slots:


    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_PDF_clicked();

    void on_modifier_clicked();

private:
    Ui::MainWindow *ui;
    employe e;


};

#endif // MAINWINDOW_H
