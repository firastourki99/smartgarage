#include "connection.h"


Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("client");
db.setUserName("firas1");
db.setPassword("firas1");

if (db.open())
test=true;





    return  test;
}
