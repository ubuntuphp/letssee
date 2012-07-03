#ifndef CUTEURL_H
#define CUTEURL_H
#include <QString>
class cuteurl
{
public:
    cuteurl();
    static bool is_url(QString url);
    static QString complete_url(QString url);
    static QString encodedurl(QString query);
};

#endif // CUTEURL_H
