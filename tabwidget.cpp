#include "tabwidget.h"
tabwidget::tabwidget(QWidget *parent) :
    QTabWidget(parent)
{
    setTabShape(QTabWidget::Triangular);
    setTabsClosable(true);
    setMovable(true);
    setStyleSheet("QTabBar::tab{color:white;background-color:red;border-color:pink;border-radius:10px;opacity:1;min-width:10px;max-width:200px;width:150px;}QTabBar::tab:selected{background-color:#75C6C6;}");
    setAcceptDrops(true);
    setElideMode(Qt::ElideRight);
    newtabbutton = new QToolButton();
    this->setCornerWidget(newtabbutton);
    newtabbutton->setToolTip("new tab");
    QObject::connect(newtabbutton , SIGNAL(clicked()) , this , SLOT(newtab()));
}
void tabwidget::dropEvent(QDropEvent * events)
{
    if(events->mimeData()->hasUrls())
    {
        emit openlinkinnewtab(events->mimeData()->urls()[0].toString());
    }
}
void tabwidget::dragEnterEvent(QDragEnterEvent *events)
{
    events->accept();
}
void tabwidget::mouseDoubleClickEvent(QMouseEvent * event)
{
    emit opennewtab();
}
void tabwidget::newtab()
{
    emit opennewtab();
}
void tabwidget::showprogress(int i, int progress)
{

}
