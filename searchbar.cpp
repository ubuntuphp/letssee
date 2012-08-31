#include "searchbar.h"
searchbar::searchbar(QWidget *parent) :
    QLineEdit(parent)
{
    setCompleter(new suggestcompleter());
    connect(this , SIGNAL(textEdited(QString)) , completer() , SLOT(suggest(QString)));
}
