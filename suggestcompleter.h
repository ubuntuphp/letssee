#ifndef SUGGESTCOMPLETER_H
#define SUGGESTCOMPLETER_H

#include <QCompleter>
#include <QStringListModel>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#define googlesuggesturl "http://google.com/complete/search?output=toolbar&q=%1"

class suggestcompleter : public QCompleter
{
    Q_OBJECT
public:
    explicit suggestcompleter(QObject *parent = 0);
    
signals:
    
public slots:
    void suggest(QString query);
private:
    QNetworkAccessManager * manager;
};

#endif // SUGGESTCOMPLETER_H
