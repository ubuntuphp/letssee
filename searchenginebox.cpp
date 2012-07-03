#include "searchenginebox.h"
searchenginebox::searchenginebox(QWidget *parent) :
    QComboBox(parent)
{
    addItem(QIcon("/home/shubhamm/real/letssee/google.png") , "google" , "http://www.google.com/search?q=");
    addItem(QIcon("/home/shubhamm/real/letssee/yahoo.png") , "yahoo" , "http://search.yahoo.com/search?p=");
    addItem(QIcon("/home/shubhamm/real/letssee/bing.png") , "bing" , "http://www.bing.com/search?q=");
    addItem(QIcon("/home/shubhamm/real/letssee/ask.png") , "ask" , "http://www.ask.com/web?q=");
}
