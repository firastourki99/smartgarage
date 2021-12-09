#include "mailing_sercice.h"
#include "ui_mailing_sercice.h"

mailing_sercice::mailing_sercice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mailing_sercice)
{
    ui->setupUi(this);
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
}

mailing_sercice::~mailing_sercice()
{
    delete ui;
}
//mailing
void  mailing_sercice::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

     ui->file->setText( fileListString );

}
void   mailing_sercice::sendMail()
{
    Smtp* smtp = new Smtp("louay.ladjimi@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("louay.ladjimi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("louay.ladjimi@esprit.tn",ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   mailing_sercice::mailSent(QString status)
{

    if(status == "Message sent")
       // QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
  //  {
  //      Notifications *notif=new Notifications();
    //    notif->show_notif("succes","message envoyé");

   // }
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}
