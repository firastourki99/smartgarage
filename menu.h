#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "mainwindow.h"
#include "firas.h"
namespace Ui {
class menu;
}

class menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::menu *ui;
    MainWindow *m;
    firas *f;
};

#endif // MENU_H
