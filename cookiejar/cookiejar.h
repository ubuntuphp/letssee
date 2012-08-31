#ifndef COOKIEJAR_H
#define COOKIEJAR_H

#include <QNetworkCookieJar>

class cookiejar : public QNetworkCookieJar
{
    Q_OBJECT
public:
    explicit cookiejar(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // COOKIEJAR_H
