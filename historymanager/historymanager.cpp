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
    query = new QSqlQuery(database);
    createtablehistory();
    tablemodel = new QSqlTableModel(this , database);
    if(database.tables().indexOf("history") == -1)
    {
        qDebug() << "database does not exists";
        qDebug() << query->exec("create table history "
                             "(id integer primary key, "
                             "title varchar(1000), "
                             "url varchar(1000),time DATETIME) "
                             );
    }
    if(database.tables().indexOf("eachhistory") == -1)
    {
        qDebug() << "database eachhistory does not exists";
        qDebug() << query->exec("create table eachhistory(id integer primary key,title varchar(1000)url varchar(1000)time DATETIME visits integer)");
    }
    tablemodel->setTable("history");
    tablemodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
}
bool historymanager::createtablehistory()
{

}
bool historymanager::addhistory(QString title, QString url , QDateTime time)
{
    qDebug() << time;
    return query->exec(tr("insert into history(title , url , time)VALUES('%1','%2','%3')").arg(title , url , time.toString()));
}
bool historymanager::addhistory(QString title, QString url)
{
    return addhistory(title , url , QDateTime::currentDateTime());
}
bool historymanager::showhistory()
{
    tablemodel->select();    tablemodel->setHeaderData(1 , Qt::Horizontal ,tr("title"));
    tablemodel->setHeaderData(2 , Qt::Horizontal , tr("url"));
    QTableView * tableview = new QTableView();
    tableview->setModel(tablemodel);
    qDebug() << tablemodel->rowCount();
    tableview->show();
}
bool historymanager::clearallhistory()
{
    query->exec("DELETE FROM history");
}
bool historymanager::addhistory(QWebHistory  * history)
{
    for(int i = 0;i < history->count();i++)
    {
        const QWebHistoryItem item = history->itemAt(i);
        addhistory(item.title() , item.url().toString() , item.lastVisited());
    }
    return true;
}
bool historymanager::updatehistory(QString url ,QString newtitle)
{
    return query->exec(QString("UPDATE history set title='%1' WHERE url='%2'").arg(newtitle,url));
}
