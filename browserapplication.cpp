#include "browserapplication.h"
QSettings * browserapplication::globalsettings = new QSettings("open devs" , "main settings");
historymanager * browserapplication::hmanager = new historymanager();
browserapplication::browserapplication(QObject *parent) :
    QObject(parent)
{
    win = new MainWindow();
    win->show();
}
void browserapplication::launchsettingseditor()
{
    settingseditor * settingseditorview = new settingseditor();
    settingseditorview->show();
}
QSettings * browserapplication::settings()
{
    return globalsettings;
}
historymanager * browserapplication::gethistorymanager()
{
    return hmanager;
}
void browserapplication::addhistory(QString url, QString title)
{
    hmanager->addhistory(title , url);
}
void browserapplication::updatehistory(QString url, QString newtitle)
{
    hmanager->updatehistory(url , newtitle);
}

