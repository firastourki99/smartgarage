#ifndef DIALOG2_H
#define DIALOG2_H

#include <QDialog>

namespace Ui {
class Dialog2;
}

class Dialog2 : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)

public:
    explicit Dialog2(QWidget *parent = nullptr);
    ~Dialog2();
    QColor color() const
    {
        return m_color;
    }

signals:
    void colorChanged(QColor color);

private slots:
    void onColorChanged();

    void on_pb_exit_clicked();

public slots:
    QString getRefColor();


private:
    Ui::Dialog2 *ui;
    QColor m_color;
};

#endif // DIALOG2_H
