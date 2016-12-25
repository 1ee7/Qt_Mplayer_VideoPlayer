#ifndef XKLOGLISTVIEW_H
#define XKLOGLISTVIEW_H

#include <QDockWidget>
#include <QListWidget>
#include <QTime>
#include <QPalette>
//#include <log4cpp/Category.hh>
//#include <log4cpp/PropertyConfigurator.hh>

class XkLogListView : public QDockWidget
{
    Q_OBJECT
private:
    explicit XkLogListView(const QString &titleNm,QDockWidget *parent = 0);
    public:
    static XkLogListView *Instance();
      ~XkLogListView();
signals:
public:
    void InitLogView();
    void RootWarn(QString );
    void RootError(QString );
     void RootInfo(QString  );
     void RootDebug(QString  );
public:
        QListWidget *pLogList;


public slots:
    
};

#endif // XKLOGLISTVIEW_H
