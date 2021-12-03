#ifndef FACTURE_H
#define FACTURE_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class facture;
}

class facture : public QDialog
{
    Q_OBJECT

public:
    explicit facture(QWidget *parent = nullptr);
    ~facture();
    bool ajouter(float);

private slots:
    void on_pb_facture2_clicked();


private:
    Ui::facture *ui;
};

#endif // FACTURE_H
