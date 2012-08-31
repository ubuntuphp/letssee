#include "settingseditor.h"

settingseditor::settingseditor(QWidget *parent) :
    QWidget(parent)
{
    settings = browserapplication::settings();
    settingstabs = new QTabWidget(this);
    searchtab = new QWidget();
    settingstabs->addTab(searchtab , "search");
    searchformlayout = new QFormLayout(searchtab);
    searchonkeyup = new QLabel("search when text editing is finished");
    choosekeyup = new QCheckBox();
    savebutton = new QPushButton("save");
    searchformlayout->addRow(searchonkeyup , choosekeyup);
    searchformlayout->addRow("" , savebutton);
    readsettings();
    QObject::connect(savebutton , SIGNAL(clicked()) , this , SLOT(savesettings()));
}
void settingseditor::writesettings(QString key, QVariant value , QString group = "")
{
    if(group != "")
    {
        settings->beginGroup(group);
    }
    settings->setValue(key , value);
    if(group != "")
    {
        settings->endGroup();
    }
}
void settingseditor::savesettings()
{
    writesettings("search on keyup" , choosekeyup->isChecked());
}
void settingseditor::readsettings()
{
    choosekeyup->setChecked(settings->value("search on keyup").toBool());
}
