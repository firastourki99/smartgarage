#ifndef EMAIL_H
#define EMAIL_H

#include <QMainWindow>
#include "smtp.h"
#include <QtWidgets/QMessageBox>
#include <QFileDialog>

namespace Ui {
class email;
}

class email : public QDialog
{
    Q_OBJECT
    
public:
    explicit email(QWidget *parent = 0);
    ~email();

private slots:
    void sendMail();
    void mailSent(QString);
    void browse();
    
private:
    Ui::email *ui;
    QStringList files;

};

#endif // MAINWINDOW_H
