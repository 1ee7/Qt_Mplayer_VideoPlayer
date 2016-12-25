#include "xkloglistview.h"
#include <qdebug.h>
static XkLogListView * pInstance_XkLogListView=NULL;

//log4cpp::Category& root = log4cpp::Category::getRoot();
//log4cpp::Category& sub1 =
//log4cpp::Category::getInstance(std::string("sub1"));
//log4cpp::Category& sub2 =
//log4cpp::Category::getInstance(std::string("sub1.sub2"));

XkLogListView::XkLogListView(const QString &titleNm, QDockWidget *parent)
    :QDockWidget(titleNm,parent)
{
       pLogList = new QListWidget(this);

//       std::string initFileName = "log4cpp.properties";
//       log4cpp::PropertyConfigurator::configure(initFileName);

       pLogList->setStyleSheet("color:green;background-color:black;");  //绿色字体黑色背景

       QWidget* lTitleBar = this->titleBarWidget();
        QWidget* lEmptyWidget = new QWidget();
        this->setTitleBarWidget(lEmptyWidget);
        delete lTitleBar;

//       pLogList->setStyleSheet("font-color:green;");

}

XkLogListView *XkLogListView::Instance()
{
    if(   pInstance_XkLogListView == NULL)
        pInstance_XkLogListView = new XkLogListView(tr("日志信息"));
    return pInstance_XkLogListView;
}
XkLogListView::~XkLogListView()
{
//       log4cpp::Category::shutdown();
}

void XkLogListView::InitLogView()
{
    pLogList->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setWidget(pLogList);
}

void XkLogListView::RootWarn(QString mwarn)
{
     pLogList->addItem(QTime::currentTime().toString("hh:mm:ss.zzz")+ " --  "+"WARM: "+mwarn);
     pLogList->scrollToBottom();
//    std::string cstr = ((const char *)mwarn.toLocal8Bit());
//    root.warn(cstr);
}

void XkLogListView::RootError(QString merro)
{
      pLogList->addItem(QTime::currentTime().toString("hh:mm:ss.zzz")+ "-- "+ "ERROR :  "+merro);
         pLogList->scrollToBottom();
//    std::string cstr = ((const char *)merro.toLocal8Bit());
//    root.error(cstr);
}

void XkLogListView::RootInfo(QString minfo)
{
      pLogList->addItem(QTime::currentTime().toString("hh:mm:ss.zzz")+ "--"+"INFO: "+minfo);
         pLogList->scrollToBottom();
//     std::string cstr = ((const char *)minfo.toLocal8Bit());
//      root.info(cstr);
}

void XkLogListView::RootDebug(QString mdebug)
{
     pLogList->addItem(QTime::currentTime().toString("hh:mm:ss.zzz")+ "-- "+"DEBUG: "+mdebug);
        pLogList->scrollToBottom();
//     std::string cstr = ((const char *)mdebug.toLocal8Bit());
//    root.debug(cstr);
}
