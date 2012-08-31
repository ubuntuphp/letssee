#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QLineEdit>
#include "suggestcompleter.h"

class searchbar : public QLineEdit
{
    Q_OBJECT
public:
    explicit searchbar(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // SEARCHBAR_H
