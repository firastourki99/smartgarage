#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnection()
{bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test");
db.setUserName("youssef");//inserer nom de l'utilisateur
db.setPassword("esprit21");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;

}
void Connection::closeconnection()
{
    db.close();
}
