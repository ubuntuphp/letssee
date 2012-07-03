#include "webview.h"
#include <QMessageBox>
webview::webview(QWidget *parent) :
    QWebView(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    settings()->setAttribute(QWebSettings::DnsPrefetchEnabled , true);
    settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows , true);
    settings()->setAttribute(QWebSettings::JavascriptCanCloseWindows , true);
    settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard , true);
    settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled , true);
    settings()->setAttribute(QWebSettings::LocalStorageEnabled , true);
    settings()->setAttribute(QWebSettings::JavaEnabled , true);
    settings()->setAttribute(QWebSettings::LocalStorageEnabled , true);
    settings()->enablePersistentStorage(QApplication::applicationDirPath());
}
void webview::contextMenuEvent(QContextMenuEvent * event)
{
    QMenu * menu = new QMenu();
    menu->setVisible(true);
    QWebHitTestResult element = this->page()->mainFrame()->hitTestContent(event->pos());
    if(!element.linkUrl().isEmpty())
    {
        QAction * newtab = this->pageAction(QWebPage::OpenLinkInNewWindow);
        newtab->setText(tr("open link in new tab"));
        menu->addAction(newtab);
        menu->addAction(this->pageAction(QWebPage::DownloadLinkToDisk));
        menu->addAction(this->pageAction(QWebPage::CopyLinkToClipboard));
    }
    if(!element.imageUrl().isEmpty())
    {
        menu->addAction(this->pageAction(QWebPage::DownloadImageToDisk));
        menu->addAction(this->pageAction(QWebPage::CopyImageToClipboard));
        menu->addAction(this->pageAction(QWebPage::CopyImageUrlToClipboard));
        QAction * newimage = this->pageAction(QWebPage::OpenImageInNewWindow);
        newimage->setText(tr("open image in new tab"));
        menu->addAction(newimage);
    }
    if(!page()->selectedText().isEmpty())
    {
        menu->addAction(this->pageAction(QWebPage::Copy));
        menu->addAction(this->pageAction(QWebPage::Cut));
        menu->addAction(this->pageAction(QWebPage::Paste));
        menu->addAction(this->pageAction(QWebPage::Undo));
        menu->addAction(this->pageAction(QWebPage::Redo));
        menu->addAction(this->pageAction(QWebPage::SelectAll));
    }
    if(element.element().tagName().toLower() == "input" && element.element().attribute(QLatin1String("type")).toLower() == "text")
    {
        menu->addAction(this->pageAction(QWebPage::SelectAll));
        menu->addAction(this->pageAction(QWebPage::Paste));
        menu->addAction(this->pageAction(QWebPage::SetTextDirectionLeftToRight));
        menu->addAction(this->pageAction(QWebPage::SetTextDirectionRightToLeft));
        menu->addAction(this->pageAction(QWebPage::SetTextDirectionDefault));
        menu->addAction(this->pageAction(QWebPage::MoveToNextWord));
    }
    if(!element.isNull())
    {
        menu->addAction(this->pageAction(QWebPage::Back));
        menu->addAction(this->pageAction(QWebPage::Forward));
        menu->addAction(this->pageAction(QWebPage::Reload));
        menu->addAction(this->pageAction(QWebPage::Stop));
        menu->addAction(this->pageAction(QWebPage::InspectElement));
    }
    menu->exec(event->globalPos());
}
QWebView * webview::createWindow(QWebPage::WebWindowType type)
{
    webview *webView = new webview;
    QWebPage *newWeb = new QWebPage(webView);
    webView->setAttribute(Qt::WA_DeleteOnClose, true);
    webView->setPage(newWeb);
    if(type == 1)
    {
        webView->show();
    }
    else if(type == 0)
    {
        emit openlinkinnewtab(webView);
    }
    return webView;
}
