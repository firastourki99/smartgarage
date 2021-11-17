#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>
#include "dialog2.h"
#include "voiture.h"
#include <QIntValidator>
#include <QColor>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QPainter>
#include <QPrintDialog>
#include <QTextTableCell>
#include <QPdfWriter>
#include <QTextBrowser>
#include <QTableView>
#include <QPrintDialog>
#include "voiture.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_color_clicked();

    QString hexcolor(int r, int g, int b);

    void on_CB_trie_currentIndexChanged(const QString &);

    void on_le_recherche_textEdited(const QString &arg1);

    void on_pb_pdf_clicked();


private:
    Ui::MainWindow *ui;
    Voiture V;

};

#endif // MAINWINDOW_H
