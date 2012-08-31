#include "suggestcompleter.h"

suggestcompleter::suggestcompleter(QObject *parent) :
    QCompleter(parent)
{
    manager = new QNetworkAccessManager(this);
    QStringListModel * model = new QStringListModel(this);
    QStringList completions;
    completions << "php" << "asp" << "python" << "qt" << "gtk" << "java" << "c++" << "c" << "haskell";
    model->setStringList(completions);
    setModel(model);
}
void suggestcompleter::suggest(QString query)
{
    QString url = QString(googlesuggesturl).arg(query);
    manager->get(QNetworkRequest(QUrl(url)));
}
