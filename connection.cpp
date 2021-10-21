#include "connection.h"
//test tutorial git
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");
db.setUserName("Ahmed");//inserer nom de l'utilisateur
db.setPassword("ahmed2001");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
