#include "dialogcharts.h"
#include "ui_dialogcharts.h"

DialogCharts::DialogCharts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCharts)
{
    ui->setupUi(this);
    paintChart();
}

DialogCharts::~DialogCharts()
{
    delete ui;
}


void DialogCharts::paintChart()
{
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(30, 142, 112));
    gradient.setColorAt(0.38, QColor(47, 174, 150));
    gradient.setColorAt(1, QColor(82, 193, 163));
    ui->widget_stat->setBackground(QBrush(gradient));


    // create empty bar chart objects:
    QCPBars *regen = new QCPBars(ui->widget_stat->xAxis, ui->widget_stat->yAxis);
    regen->setAntialiased(false); // gives more crisp, pixel aligned bar borders

    // set names and colors:
    regen->setName("Voitures  ");
    regen->setPen(QPen(QColor(0, 168, 140).lighter(180)));
    regen->setBrush(QColor(18,45,38));


    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    QVector<double> regenData;


    ticks << 1 << 2 << 3 << 4 << 5 ;
    QSqlQuery q;
    q.prepare("select D_D_D ,count(MATRICULE) from VOITURE group by D_D_D  ");

    if(q.exec()){
        while (q.next()) {
            labels << q.value(3).toString();

            regenData   << q.value(1).toDouble();
        }
    }
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);

    ui->widget_stat->xAxis->setTicker(textTicker);
    ui->widget_stat->xAxis->setTickLabelRotation(60);
    ui->widget_stat->xAxis->setTickLength(0, 4);
    ui->widget_stat->xAxis->setRange(0, 4);
    ui->widget_stat->xAxis->setLabel("nombre de voitures");

    ui->widget_stat->xAxis->setBasePen(QPen(Qt::white));
    ui->widget_stat->xAxis->setTickPen(QPen(Qt::white));
    ui->widget_stat->xAxis->grid()->setVisible(true);
    ui->widget_stat->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->widget_stat->xAxis->setTickLabelColor(Qt::white);
    ui->widget_stat->xAxis->setLabelColor(Qt::white);


    ui->widget_stat->yAxis->setRange(1,10);
    ui->widget_stat->yAxis->setPadding(5); // a bit more space to the left border
    ui->widget_stat->yAxis->setLabel("identifiant");
    ui->widget_stat->yAxis->setBasePen(QPen(Qt::white));
    ui->widget_stat->yAxis->setTickPen(QPen(Qt::white));
    ui->widget_stat->yAxis->setSubTickPen(QPen(Qt::white));
    ui->widget_stat->yAxis->grid()->setSubGridVisible(true);
    ui->widget_stat->yAxis->setTickLabelColor(Qt::white);
    ui->widget_stat->yAxis->setLabelColor(Qt::white);
    ui->widget_stat->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->widget_stat->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    regen->setData(ticks, regenData);

    // setup legend:
    ui->widget_stat->legend->setVisible(true);
    ui->widget_stat->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->widget_stat->legend->setBrush(QColor(255, 255, 255, 100));
    ui->widget_stat->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->widget_stat->legend->setFont(legendFont);
    ui->widget_stat->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    /**********************************************************************************/
}


