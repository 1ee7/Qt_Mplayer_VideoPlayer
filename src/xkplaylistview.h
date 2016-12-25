#ifndef XKVIDEOLIST_H
#define XKVIDEOLIST_H

#include <QDockWidget>
#include <QListWidget>
#include <QMenu>
#include <QListWidgetItem>
#include <QMap>
#include <QFileInfo>
#include <QFileDialog>
#include <QDataStream>
#include<QFile>
#include <QMessageBox>
#include <qdebug.h>
#include "xkloglistview.h"

class XkPlayListView: public QDockWidget
{
    Q_OBJECT
public:
    static XkPlayListView *Instance();
private:
        explicit XkPlayListView(const QString &titleNm,QDockWidget *parent = 0);
public:
         void  InitListView();
         void AddItem(QString);
         QString PlayListNextFile();
         QString PlayListPreFile();

signals:
         void sPlayVideo(QString);
    
public slots:
         void OnRightClicked(QPoint );
         void RemoveFromList();
         void OnPlayVideo();
         void SavePlayList();
         void LoadPlayList();

private:
//             QListWidget * pPlayList ;

public:
              QListWidget * pPlayList ;
             QStringList    mPlayFileList;
             QMap <QString,QString> mPlaylistMap;
              XkLogListView *pLogListView;
    
};

#endif // XKVIDEOLIST_H
