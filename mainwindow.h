#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"

#include <QMainWindow>

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


    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_PDF_clicked();

private:
    Ui::MainWindow *ui;
    employe e;


};

#endif // MAINWINDOW_H
