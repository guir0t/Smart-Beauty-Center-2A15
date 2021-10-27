#include "connection.h"

connection::connection(){}
bool connection::createConnection()
{
    db= QSqlDatabase::addDatabase("QODBC");
    bool test=false ;
    db.setDatabaseName("test-bd");
    db.setUserName("system");
    db.setPassword("123");
    if (db.open()) test=true;
    return test;
}
void connection::closeConnection()
{
    db.close();
}
