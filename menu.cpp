#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_clicked()
{
    m = new MainWindow(this);
    m->show();
}

void menu::on_pushButton_2_clicked()
{
    f = new firas(this);
    f->show();
}
