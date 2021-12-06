#include "connection.h"


Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("client1");
db.setUserName("firas1");
db.setPassword("firas1");

if (db.open())
test=true;





    return  test;
}
void Connection::closeconnection(){db.close();}
