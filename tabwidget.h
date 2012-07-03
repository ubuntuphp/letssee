#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QTabBar>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QUrl>
#include <QMouseEvent>
#include <QToolButton>
class tabwidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit tabwidget(QWidget *parent = 0);
    QToolButton * newtabbutton;
signals:
    void openlinkinnewtab(QString url);
    void opennewtab();
public slots:
    void newtab();
    void showprogress(int i , int progress);
protected:
    virtual void dropEvent(QDropEvent * events);
    virtual void dragEnterEvent(QDragEnterEvent * events);
    virtual void mouseDoubleClickEvent(QMouseEvent * event);
};

#endif // TABWIDGET_H
