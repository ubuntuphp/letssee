#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebView>
#include <QAction>
#include <QMenu>
#include <QUrl>
#include <QContextMenuEvent>
#include <QWebFrame>
#include <QWebElement>
#include <QWebHitTestResult>
#include <QApplication>
class webview : public QWebView
{
    Q_OBJECT
public:
    explicit webview(QWidget *parent = 0);
signals:
    void openlinkinnewtab(QString url);
    void openlinkinnewtab(webview * webpage);
public slots:
    void contextMenuEvent(QContextMenuEvent * event);
private slots:
private:
protected:
    virtual QWebView * createWindow(QWebPage::WebWindowType type);
};

#endif // WEBVIEW_H
