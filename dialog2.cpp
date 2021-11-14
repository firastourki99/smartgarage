#include "dialog2.h"
#include "ui_dialog2.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    connect(ui->redSlide, SIGNAL(valueChanged(int)), SLOT(onColorChanged()));
    connect(ui->blueSlide, SIGNAL(valueChanged(int)), SLOT(onColorChanged()));
    connect(ui->greenSlide, SIGNAL(valueChanged(int)), SLOT(onColorChanged()));
    onColorChanged();
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::onColorChanged()
{
    m_color.setRgb(ui->redSlide->value(), ui->blueSlide->value(), ui->greenSlide->value());
    QPalette pal = ui->displayWidget->palette();
    pal.setColor(QPalette::Window, m_color);
    ui->displayWidget->setPalette(pal);
    emit colorChanged(m_color);
}
