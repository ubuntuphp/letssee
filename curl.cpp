#include "curl.h"

curl::url()
{
}
bool curl::isurl(QString url)
{
    if(!url.startsWith("http") || url.startsWith("https"))
    {
        if(url.startsWith("www"))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
