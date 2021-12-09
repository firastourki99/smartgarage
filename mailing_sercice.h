#ifndef MAILING_SERCICE_H
#define MAILING_SERCICE_H

#include <QDialog>
#include <QFileDialog>
#include "smtp.h"
#include <QDialog>

namespace Ui {
class mailing_sercice;
}

class mailing_sercice : public QDialog
{
    Q_OBJECT

public:
    explicit mailing_sercice(QWidget *parent = nullptr);
    ~mailing_sercice();

private:
    Ui::mailing_sercice *ui;
    QStringList files;
private slots:

    //mailing
    void sendMail();
    void mailSent(QString);
    void browse();

  //  void on_pushButton_clicked();
};
#endif // MAILING_SERCICE_H
