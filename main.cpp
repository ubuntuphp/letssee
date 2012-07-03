#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QWebSettings>
#include <QDir>
#include <QDesktopServices>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("cute browser");
    a.setOrganizationName("open devs");
    QWebSettings::setIconDatabasePath(a.applicationDirPath());
    QWebSettings::setOfflineStoragePath(a.applicationDirPath());
    MainWindow w;
    w.show();
    return a.exec();
}
