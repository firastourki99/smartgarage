#ifndef DIALOGCHARTS_H
#define DIALOGCHARTS_H

#include <QDialog>
#include <QSqlQuery>
namespace Ui {
class DialogCharts;
}

class DialogCharts : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCharts(QWidget *parent = nullptr);
    ~DialogCharts();

private:
    Ui::DialogCharts *ui;
};

#endif // DIALOGCHARTS_H
