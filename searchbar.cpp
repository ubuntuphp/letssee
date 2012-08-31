#include "searchbar.h"
searchbar::searchbar(QWidget *parent) :
    QLineEdit(parent)
{
    setCompleter(new suggestcompleter());
}
