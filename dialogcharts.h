#ifndef DIALOGCHARTS_H
#define DIALOGCHARTS_H

#include <QtSql>
#include<QMap>
#include <iostream>
#include <QString>
#include<time.h>
#include <QDialog>
#include <qdialog.h>
#include <ctime>
#include<vector>
#include <QLineEdit>
#include <cstring>
#include <QSharedPointer>
#include<QSharedDataPointer>
#include<qsharedpointer.h>
#include<qcustomplot.h>
#include <QDialog>
#include <QtWidgets/QMessageBox>
#include <QFileDialog>
#include <QDebug>


namespace Ui {
class DialogCharts;
}

class DialogCharts : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCharts(QWidget *parent = nullptr);
    ~DialogCharts();
protected:
    void paintChart();
private:
    Ui::DialogCharts *ui;
    QStringList files;
};

#endif // DIALOGCHARTS_H
