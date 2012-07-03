#ifndef URL_H
#define URL_H
#include <QString>
#include <QRegExp>
class curl
{
public:
    curl();
    static bool isurl(QString url);
};

#endif // URL_H
