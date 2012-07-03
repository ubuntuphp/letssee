#include "historymanager.h"
#include <QDebug>
historymanager::historymanager(QObject *parent) :
    QObject(parent)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setHostName("cute browser");
    database.setUserName("cute browser");
    database.setPassword("password");
    database.setDatabaseName("cute browser");
    bool ok = database.open();
    qDebug() << ok;
    createtablehistory();
    query = new QSqlQuery(database);
}
bool historymanager::createtablehistory()
{
    //qDebug() << query->exec("create table history(id integer primary key,firstname varchar(20),lastname varchar(30)age integer)");
}
bool historymanager::addhistory(QString title, QString url)
{
    qDebug() << query->exec("insert into history(title ,url)VALUES(" + title + "," + url + ")");
}
