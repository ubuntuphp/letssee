#include "cuteurl.h"
cuteurl::cuteurl()
{
}
bool cuteurl::is_url(QString url)
{
    if(url.startsWith("http") or url.startsWith("https"))
    {
        return true;
    }
    if(url.startsWith("www"))
    {
        return true;
    }
    return false;
}
QString cuteurl::complete_url(QString url)
{
    QString completeurl;
    if(url.startsWith("www"))
    {
        completeurl = "http://" + url;
        return completeurl;
    }
    return url;
}
QString cuteurl::encodedurl(QString query)
{
    query.replace("!" , "%21");
    query.replace("#" , "%23");
    query.replace("$" , "%24");
    query.replace("&" , "%26");
    query.replace("'" , "%27");
    query.replace("(" , "%28");
    query.replace(")" , "%29");
    query.replace("*" , "%2A");
    query.replace("+" , "%2B");
    query.replace("," , "%2C");
    query.replace("/" , "%2F");
    query.replace(":" , "%3A");
    query.replace(";" , "%3B");
    query.replace("=" , "%3D");
    query.replace("?" , "%3F");
    query.replace("@" , "%40");
    query.replace("[" , "%5B");
    query.replace("]" , "%5D");
    return query;
}
