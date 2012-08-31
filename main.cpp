#include <QtGui/QApplication>
#include <QWebSettings>
#include <QDir>
#include <QDesktopServices>
#include "browserapplication.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("cute browser");
    a.setOrganizationName("open devs");
    QWebSettings::setIconDatabasePath(a.applicationDirPath());
    QWebSettings::setOfflineStoragePath(a.applicationDirPath());
    browserapplication * app = new browserapplication();
    return a.exec();
}
