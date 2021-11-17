#include "dialogcharts.h"
#include "ui_dialogcharts.h"

DialogCharts::DialogCharts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCharts)
{
    ui->setupUi(this);
}

DialogCharts::~DialogCharts()
{
    delete ui;
}

