#ifndef XKFILETREEVIEW_H
#define XKFILETREEVIEW_H
#include <QDockWidget>
#include<QFileSystemModel>
#include <QTreeView>
#include <QHeaderView>
#include <QModelIndex>
#include <QMenu>
#include "xkplaylistview.h"

class XkFileTreeView : public QDockWidget
{
    Q_OBJECT
private:
      XkFileTreeView(const QString &titleNm,QDockWidget *parent=0);

          bool IsPlayFile( );
public:
   static XkFileTreeView *Instance();
   void InitFileTree();

public slots:
   void OnLeftClicked(const QModelIndex&);
   void OnRightClicked(const QPoint &);
   void Add2List();
   void PlayVideo();



signals:
    void  sFileTreeLetfClicked(QString);
    void  sFileTreePlayVideo(QString);
    void  sFileTreeAdd2list(QString);

public:
                    QTreeView   *pTreeView;
   QFileSystemModel  *pFileSystemModel;
                           QString     mFileNamePath;
                   QStringList     mFileTypeList ;
           XkPlayListView *pPlayListView;


};

#endif // XKFILETREEVIEW_H
