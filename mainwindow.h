#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QWebView>
#include "webview.h"
#include "cuteurl.h"
#include "tabwidget.h"
#include "searchbar.h"
#include <QTabWidget>
#include <QWebHistory>
#include <QSettings>
#include "searchenginebox.h"
#include "locaionbar.h"
#include <QDebug>
#include <QFileInfo>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    searchenginebox * searchbox;
    QSettings * settings;
    searchbar * searchedit;
    QStringList closedtabs;
    locaionbar * locationbar;
    webview * webpage;
    tabwidget * tabs;
    QAction * forwardAction;
    QAction * backAction;
    QAction * stopAction;
    QAction * reloadAction;
    QAction * homeaction;
    QWebHistory * history;
    QMenu * recentlyclosedtabs;
public slots:
    void addrecentlyclosedtabs(webview *page);
    void loadurl();
    void loadurl(QString url);
    webview * newtab(QString url);
    webview * newtab();
    webview * newtab(webview * page);
    void setcurrentwebpage(int index);
    webview *startuptabs();
    void updatetabtitle(QString title);
    void updatelocation(QUrl url);
    void updateconnections();
    void updateaction();
    void updateicon();
    void closetab(int index);
    void back();
    void forward();
    void reload();
    void stop();
    void search(QString query);
    void search();
    void openrecentlyclosedtab(QAction * action);
    void restoreprevioussession();
    void addtohomepages(QString url);
    void updateprogress(int i);
    void setfinished();
    void showlink(QString link);
    void savewindowstate();
    void restorewindowstate();
private slots:
    void on_actionNew_tab_triggered();

    void on_actionRestore_previous_session_triggered();

    void on_actionAdd_to_home_page_triggered();

    void on_actionTool_bar_triggered();

    void on_actionShow_all_history_triggered();

    void on_actionClear_all_history_triggered();

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;
protected:
    void closeEvent(QCloseEvent * event);
};

#endif // MAINWINDOW_H
