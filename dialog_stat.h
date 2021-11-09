#ifndef DIALOG_STAT_H
#define DIALOG_STAT_H

#include <QDialog>
#include <QtWidgets/QMessageBox>
#include <QFileDialog>

namespace Ui {
class Dialog_stat;
}

class Dialog_stat : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_stat(QWidget *parent = nullptr);
    ~Dialog_stat();

private:
    Ui::Dialog_stat *ui;
    QStringList files;
};

#endif // DIALOG_STAT_H
