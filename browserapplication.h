#ifndef BROWSERAPPLICATION_H
#define BROWSERAPPLICATION_H

#include <QObject>
#include "mainwindow.h"
#include "settingseditor.h"
#include "historymanager/historymanager.h"
class browserapplication : public QObject
{
    Q_OBJECT
public:
    explicit browserapplication(QObject *parent = 0);
    MainWindow * win;
signals:
    
public slots:
    static void launchsettingseditor();
    static historymanager * gethistorymanager();
    static void addhistory(QString url , QString title);
    static void updatehistory(QString url , QString newtitle);
    static QCompleter * historycompletor();
    static QSettings *settings();
private:
    static QSettings * globalsettings;
    static historymanager * hmanager;
};

#endif // BROWSERAPPLICATION_H
