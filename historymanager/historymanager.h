#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QApplication>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlError>
#include <QWebHistory>
#include <QWebHistoryItem>
#include <QDateTime>
#include <QCompleter>
class historymanager : public QObject
{
    Q_OBJECT
public:
    QSqlQuery * query;
    explicit historymanager(QObject *parent = 0);
    QSqlDatabase database;
    QSqlTableModel * tablemodel;
signals:
    
public slots:
    bool createtablehistory();
    bool addhistory(QString title , QString url, QDateTime time);
    bool addhistory(QString title , QString url);
    bool updatehistory(QString url , QString newtitle);
    bool addhistory(QWebHistory *history);
    bool showhistory();
    bool clearallhistory();
    QCompleter * historycompletor();
};

#endif // HISTORYMANAGER_H
