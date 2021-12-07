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
    ui->le_hex->setEnabled(false);
    onColorChanged();
}

Dialog2::~Dialog2()
{
    delete ui;
}



void Dialog2::onColorChanged()
{
    m_color.setRgb(ui->redSlide->value(),ui->greenSlide->value(), ui->blueSlide->value());
    QPalette pal = ui->displayWidget->palette();
    pal.setColor(QPalette::Window, m_color);
    ui->displayWidget->setPalette(pal);
    emit colorChanged(m_color);
    QColor m_color = QColor(ui->redSpinBox->value(), ui->blueSpinBox->value()
                            ,ui->greenSpinBox->value());
    QString m_str = m_color.name();
    ui->le_hex->setText(m_str);

}

QString Dialog2::getRefColor()
{
    return ui->le_hex->text();
}



void Dialog2::on_pb_exit_clicked()
{
    close();
}
