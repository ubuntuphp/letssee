#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "browserapplication.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    settings = browserapplication::settings();
    ui->setupUi(this);
    locationbar = new locaionbar();
    tabs = new tabwidget();
    searchedit = new searchbar();
    webpage = startuptabs();
    searchbox = new searchenginebox();
    forwardAction = new QAction(QIcon::fromTheme("go-next") , tr("forward") , this);
    backAction = new QAction(QIcon::fromTheme("go-previous") , tr("back") , this);
    stopAction = new QAction(QIcon::fromTheme("process-stop") , tr("stop") , this);
    reloadAction = new QAction(QIcon::fromTheme("view-refresh") , tr("reload") , this);
    homeaction = new QAction(QIcon::fromTheme("go-home") , tr("home page") , this);
    ui->mainToolBar->addAction(forwardAction);
    ui->mainToolBar->addAction(backAction);
    ui->mainToolBar->addAction(stopAction);
    ui->mainToolBar->addAction(reloadAction);
    ui->mainToolBar->addWidget(locationbar);
    ui->mainToolBar->addWidget(searchbox);
    ui->mainToolBar->addWidget(searchedit);
    ui->mainToolBar->addAction(homeaction);
    ui->mainToolBar->setFixedHeight(30);
    recentlyclosedtabs = new QMenu("recently closed tabs");
    ui->menuHistory->addMenu(recentlyclosedtabs);
    searchedit->setFixedWidth(300);
    setCentralWidget(tabs);
    QObject::connect(forwardAction , SIGNAL(triggered()) , this , SLOT(forward()));
    QObject::connect(backAction , SIGNAL(triggered()) , this , SLOT(back()));
    QObject::connect(stopAction , SIGNAL(triggered()) , this , SLOT(stop()));
    QObject::connect(reloadAction , SIGNAL(triggered()) , this , SLOT(reload()));
    QObject::connect(locationbar , SIGNAL(returnPressed()) , this , SLOT(loadurl()));
    QObject::connect(tabs , SIGNAL(currentChanged(int)) , this , SLOT(setcurrentwebpage(int)));
    QObject::connect(webpage , SIGNAL(titleChanged(QString)) , this , SLOT(setWindowTitle(QString)));
    QObject::connect(webpage , SIGNAL(urlChanged(QUrl)) , this , SLOT(updatelocation(QUrl)));
    QObject::connect(webpage , SIGNAL(openlinkinnewtab(QString)) , this , SLOT(newtab(QString)));
    QObject::connect(tabs , SIGNAL(tabCloseRequested(int)) , this , SLOT(closetab(int)));
    QObject::connect(webpage , SIGNAL(urlChanged(QUrl)) , this , SLOT(updateaction()));
    QObject::connect(webpage , SIGNAL(openlinkinnewtab(webview*)) , this , SLOT(newtab(webview*)));
    QObject::connect(webpage->page() , SIGNAL(linkHovered(QString,QString,QString)) , this , SLOT(showlink(QString)));
    if(settings->contains("search on keyup") && settings->value("search on keyup") == true)
    {
        QObject::connect(searchedit , SIGNAL(textEdited(QString)) , this , SLOT(search(QString)));
    }
    QObject::connect(searchedit , SIGNAL(returnPressed()) , this , SLOT(search()));
    QObject::connect(tabs , SIGNAL(openlinkinnewtab(QString)) , this , SLOT(newtab(QString)));
    QObject::connect(tabs , SIGNAL(opennewtab()) , this , SLOT(newtab()));
    QObject::connect(recentlyclosedtabs , SIGNAL(triggered(QAction*)) , this , SLOT(openrecentlyclosedtab(QAction*)));
    restorewindowstate();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::loadurl()
{
    QString loadurl = locationbar->text();
    if(QUrl(loadurl).isLocalFile())
    {
        qDebug() << "yeyeye";
        this->loadurl(loadurl);
        return;
    }
    if(cuteurl::is_url(loadurl))
    {
        loadurl = cuteurl::complete_url(loadurl);
        webpage->load(QUrl(loadurl));
    }
    else
    {
        search(loadurl);
    }
}
void MainWindow::loadurl(QString url)
{
    webpage->load(QUrl(url));
}
webview * MainWindow::newtab()
{
    webview * newwebpage = new webview();
    tabs->addTab(newwebpage , newwebpage->icon() , tr("new tab"));
    QObject::connect(newwebpage , SIGNAL(titleChanged(QString)) , this , SLOT(updatetabtitle(QString)));
    QObject::connect(newwebpage , SIGNAL(iconChanged()) , this , SLOT(updateicon()));
    QObject::connect(newwebpage , SIGNAL(loadFinished(bool)) , this , SLOT(setfinished()));
    QObject::connect(newwebpage  , SIGNAL(loadProgress(int)) , this , SLOT(updateprogress(int)));
    return newwebpage;
}
webview * MainWindow::newtab(QString url)
{
    webview * newwebpage = newtab();
    newwebpage->load(QUrl(url));
    if(newwebpage->title() != "")
    {
        const QString title = newwebpage->title();
    }
    const QString title = url;
    tabs->addTab(newwebpage , newwebpage->icon() ,  title);
    return newwebpage;
}
webview * MainWindow::newtab(webview *page)
{
    webview * nwebpage = newtab();
    nwebpage->setPage(page->page());
    return nwebpage;
}
void MainWindow::search()
{
    search(searchedit->text());
}
void MainWindow::search(QString query)
{
    QString searchurl = searchbox->itemData(searchbox->currentIndex()).toString();
    loadurl(searchurl + QUrl::toPercentEncoding(query));
}
void MainWindow::setcurrentwebpage(int index)
{
    webpage = qobject_cast<webview *>(tabs->widget(index));
    locationbar->setText(webpage->url().toString());
    setWindowTitle(webpage->title());
    updateconnections();
    updateaction();
}
webview * MainWindow::startuptabs()
{
    QString url;
    if(settings->value("home page").toStringList().count() == 0 || settings->contains("home page") == false)
    {
        qDebug() << "yeah";
        webpage = newtab();
    }
    else
    {
        foreach(url , settings->value("home page").toStringList())
        {
            webpage = newtab(url);
        }
    }
    return webpage;
}
void MainWindow::updatetabtitle(QString title)
{
    webview * cwebview = qobject_cast<webview *>(sender());
    const QString newtitle = title;
    if(!cwebview->title().isEmpty())
    {
        const QString newtitle = cwebview->url().toString();
    }
    tabs->setTabText(tabs->indexOf(cwebview) , newtitle);
}
void MainWindow::updatelocation(QUrl url)
{
    statusBar()->showMessage(tr("load started") , 1000);
    locationbar->setText(url.toString());
}
void MainWindow::updateicon()
{
     webview * cwebview = qobject_cast<webview *>(sender());
     tabs->setTabIcon(tabs->indexOf(cwebview) ,cwebview->icon());
}
void MainWindow::updateconnections()
{
    QObject::disconnect(webpage , SIGNAL(openlinkinnewtab(QString)) , this , SLOT(newtab(QString)));
    QObject::disconnect(webpage , SIGNAL(titleChanged(QString)) , this , SLOT(setWindowTitle(QString)));
    QObject::disconnect(webpage , SIGNAL(urlChanged(QUrl)) , this , SLOT(updatelocation(QUrl)));
    QObject::disconnect(webpage , SIGNAL(openlinkinnewtab(webview*)) , this , SLOT(newtab(webview*)));
    QObject::disconnect(webpage , SIGNAL(urlChanged(QUrl)) , this , SLOT(updateaction()));
    QObject::disconnect(webpage->page() , SIGNAL(linkHovered(QString,QString,QString)) , this , SLOT(showlink(QString)));
    QObject::connect(webpage->page() , SIGNAL(linkHovered(QString,QString,QString)) , this , SLOT(showlink(QString)));
    QObject::connect(webpage , SIGNAL(openlinkinnewtab(QString)) , this , SLOT(newtab(QString)));
    QObject::connect(webpage , SIGNAL(openlinkinnewtab(webview*)) , this , SLOT(newtab(webview*)));
    QObject::connect(webpage , SIGNAL(titleChanged(QString)) , this , SLOT(setWindowTitle(QString)));
    QObject::connect(webpage , SIGNAL(urlChanged(QUrl)) , this , SLOT(updatelocation(QUrl)));
    QObject::connect(webpage , SIGNAL(urlChanged(QUrl)) , this , SLOT(updateaction()));
}
void MainWindow::updateaction()
{
    history = webpage->history();
    if(!history->canGoForward())
    {
        forwardAction->setEnabled(false);
    }
    else
    {
        forwardAction->setEnabled(true);
    }
    if(!history->canGoBack())
    {

        backAction->setEnabled(false);
    }
    else
    {
        backAction->setEnabled(true);
    }
}
void MainWindow::closetab(int index)
{
    const int oldtabindex = tabs->currentIndex();
    if(oldtabindex == index)
    {
    webpage = 0;
    }
    if(tabs->count() == 1)
    {
        newtab();
    }
    else if(oldtabindex == index)
    {
        setcurrentwebpage(tabs->currentIndex());
    }
    webview * cwebpage = qobject_cast<webview *>(tabs->widget(index));
    addrecentlyclosedtabs(cwebpage);
    tabs->removeTab(index);
}
void MainWindow::addrecentlyclosedtabs(webview * page)
{
    closedtabs.append(page->url().toString());
    if(page->url().toString().isEmpty())return;
    QAction * action = new QAction(page->title() , this);
    action->setData(QVariant(page->url().toString()));
    recentlyclosedtabs->addAction(action);
}
void MainWindow::updateprogress(int i)
{
    tabs->setTabText(tabs->indexOf(qobject_cast<webview *>(sender())) , tr("%1 %2").arg(QString::number(i) , qobject_cast<webview *>(sender())->title()));
}
void MainWindow::setfinished()
{
    tabs->setTabText(tabs->indexOf(qobject_cast<webview *>(sender())) , qobject_cast<webview *>(sender())->title());
}
void MainWindow::forward()
{
    webpage->forward();
}
void MainWindow::back()
{
    webpage->back();
}
void MainWindow::reload()
{
    webpage->reload();
}
void MainWindow::stop()
{
    webpage->stop();
}
void MainWindow::showlink(QString link)
{
    statusBar()->showMessage(link);
}
void MainWindow::openrecentlyclosedtab(QAction *action)
{
    newtab(action->data().toString());
    recentlyclosedtabs->removeAction(action);
}
void MainWindow::on_actionNew_tab_triggered()
{
    newtab();
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    QStringList lastsession;
    for(int i=0;i<tabs->count();i++)
    {
        lastsession.append(qobject_cast<webview *>(tabs->widget(i))->url().toString());
    }
    settings->setValue("last session" , lastsession);
    savewindowstate();
}
void MainWindow::restoreprevioussession()
{
    QStringList pagestoopen = settings->value("last session").toStringList();
    QString page;
    foreach(page , pagestoopen)
    {
        newtab(page);
    }
}
void MainWindow::on_actionRestore_previous_session_triggered()
{
    restoreprevioussession();
}

void MainWindow::on_actionAdd_to_home_page_triggered()
{
    addtohomepages(webpage->url().toString());
}
void MainWindow::addtohomepages(QString url)
{
    QStringList homepages = settings->value("home page").toStringList();
    if(homepages.contains(url))
    {
        qDebug() << url;
        qDebug() << homepages.removeOne(url);
    }
    else
    {
    homepages.append(url);
    }
    settings->setValue("home page",homepages);
}
void MainWindow::savewindowstate()
{
    settings->beginGroup("gui state");
    if(isMaximized())
    {
        settings->setValue("maximized" , true);
    }
    else
    {
        settings->remove("maximized");
        settings->setValue("window width" , width());
        settings->setValue("window height" , height());
    }
    qDebug() << ui->mainToolBar->isVisible();
    settings->setValue("tool bar visible" , ui->mainToolBar->isVisible());
    settings->endGroup();
}
void MainWindow::restorewindowstate()
{
    settings->beginGroup("gui state");
    if(settings->contains("maximized"))
    {
        showMaximized();
    }
    else if(settings->contains("window width") && settings->contains("window height"))
    {
    resize(settings->value("window width").toInt() , settings->value("window height").toInt());
    }
    if(settings->contains("tool bar visible"))
    {
        ui->actionTool_bar->setChecked(settings->value("tool bar visible").toBool());
        ui->mainToolBar->setVisible(settings->value("tool bar visible").toBool());
    }
    settings->endGroup();
}
void MainWindow::on_actionTool_bar_triggered()
{
    if(ui->mainToolBar->isVisible())
    {
    ui->mainToolBar->hide();
    ui->actionTool_bar->setChecked(false);
    }
    else
    {
    ui->mainToolBar->show();
    ui->actionTool_bar->setChecked(true);
    }
}

void MainWindow::on_actionShow_all_history_triggered()
{
    browserapplication::gethistorymanager()->showhistory();
}

void MainWindow::on_actionClear_all_history_triggered()
{
    browserapplication::gethistorymanager()->clearallhistory();
}

void MainWindow::on_actionSettings_triggered()
{
    browserapplication::launchsettingseditor();
}
