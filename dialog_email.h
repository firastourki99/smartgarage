#ifndef DIALOG_EMAIL_H
#define DIALOG_EMAIL_H

#include <QDialog>
#include "smtp.h"
#include <QtWidgets/QMessageBox>
#include <QFileDialog>

namespace Ui {
class Dialog_email;
}

class Dialog_email : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_email(QWidget *parent = nullptr);
    ~Dialog_email();
private slots:
    void sendMail();
    void mailSent(QString);
    void browse();



private:
    Ui::Dialog_email *ui;
    QStringList files;
};

#endif // DIALOG_EMAIL_H
