#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
class Client
{
public:
    Client();
    Client(int,int, QString,QString,QString,QString,QString);

    int getnum();
    int getcin();
    QString getnom();
    QString getprenom();
    QString getadr();
    QString getmail();
    QString getvoiture();


    void setnum(int);
    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void setadr(QString);
    void setmail(QString);
    void setvoiture(QString);
    bool ajouter();


private:
    int cin,num;
    QString nom, prenom, adresse, mail, num_tel, voiture;
};

#endif // CLIENT_H
