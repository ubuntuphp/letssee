#include "suggestcompleter.h"

suggestcompleter::suggestcompleter(QObject *parent) :
    QCompleter(parent)
{
    manager = new QNetworkAccessManager(this);
    model = new QStringListModel(this);
    setModel(model);
    connect(manager , SIGNAL(finished(QNetworkReply*)) , this , SLOT(handlenetworkdata(QNetworkReply*)));
}
void suggestcompleter::suggest(QString query)
{
    QString url = QString(googlesuggesturl).arg(query);
    manager->get(QNetworkRequest(QUrl(url)));
    qDebug() << "suggest";
}
void suggestcompleter::handlenetworkdata(QNetworkReply *networkreply)
{
    if(!networkreply->error())
    {
        QStringList wordlist;
        QByteArray response(networkreply->readAll());
        QXmlStreamReader xml(response);
        while(!xml.atEnd())
        {
            xml.readNext();
            if(xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if(xml.name() == "suggestion")
                {
                    QStringRef data = xml.attributes().value("data");
                    wordlist << data.toString();
                }
            }
        }
    model->setStringList(wordlist);
    popup()->setFocus();
    popup()->show();
    }
}
