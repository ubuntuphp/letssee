#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
class historymanager : public QObject
{
    Q_OBJECT
public:
    QSqlQuery * query;
    explicit historymanager(QObject *parent = 0);
    QSqlDatabase database;
signals:
    
public slots:
    bool createtablehistory();
    bool addhistory(QString title , QString url);
};

#endif // HISTORYMANAGER_H
