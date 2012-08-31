#ifndef SETTINGSEDITOR_H
#define SETTINGSEDITOR_H

#include <QWidget>
#include <QTabWidget>
#include <QFormLayout>
#include <QLabel>
#include <QCheckBox>
#include <QSettings>
#include "browserapplication.h"
#include <QPushButton>
class settingseditor : public QWidget
{
    Q_OBJECT
public:
    explicit settingseditor(QWidget *parent = 0);
    QSettings * settings;
    QTabWidget * settingstabs;
    QWidget * searchtab;
    QFormLayout * searchformlayout;
    QLabel * searchonkeyup;
    QCheckBox * choosekeyup;
    QPushButton * savebutton;
signals:
    
public slots:
    void writesettings(QString key , QVariant value, QString group);
    void savesettings();
    void readsettings();
};

#endif // SETTINGS_H
