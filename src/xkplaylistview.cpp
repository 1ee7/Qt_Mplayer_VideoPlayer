#include "xkplaylistview.h"
#include <qdebug.h>

static XkPlayListView *pInstance_XkPlayListView= NULL;

XkPlayListView::XkPlayListView(const QString &titleNm, QDockWidget *parent)
    :QDockWidget(titleNm,parent)
{
    pPlayList = new QListWidget(this);
    pLogListView = XkLogListView::Instance();
            this->setStyleSheet("color:green"); //绿色字体黑色背景
    QWidget* lTitleBar = this->titleBarWidget();
     QWidget* lEmptyWidget = new QWidget();
     this->setTitleBarWidget(lEmptyWidget);
     delete lTitleBar;
}

XkPlayListView *XkPlayListView::Instance()
{
    if(pInstance_XkPlayListView==NULL)
        pInstance_XkPlayListView = new XkPlayListView(tr("播放列表"));
    return pInstance_XkPlayListView;
}

void XkPlayListView::InitListView()
{
        pPlayList->setContextMenuPolicy(Qt::CustomContextMenu);
       this->setWidget(pPlayList);

        connect(pPlayList,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(OnRightClicked(QPoint)));
  }

void XkPlayListView::AddItem(QString mlistfile)
{
 ///NOTE HERE
  //  if(mPlayFileList.contains(mlistfile)) return;
    if(mPlaylistMap.contains(mlistfile)) return;

     QFileInfo   mCurrentFileInfo = QFileInfo(mlistfile);
     QString m_filename=mCurrentFileInfo.completeBaseName();
       mPlaylistMap.insert(mlistfile,m_filename);
      pPlayList->addItem(m_filename);

      pLogListView->RootInfo("[Add] Video"+m_filename+" To Playlist ");
}

QString XkPlayListView::PlayListNextFile()
{
    if(mPlaylistMap.isEmpty())
    {
           pLogListView->RootError(" PlayList is empty"); return "NULL";
    }
    int mIndex =  pPlayList->currentRow();
           mIndex++;
     if(mIndex  >=  mPlaylistMap.size())  mIndex =  mPlaylistMap.size()-1;
         pPlayList->item(mIndex)->setSelected(true);
        pPlayList->setCurrentRow(mIndex);

        pLogListView->RootDebug("Current Row  "+QString::number(mIndex)+" In Playlist ");
        pLogListView->RootInfo("[Play Next Video] "+ pPlayList->item(mIndex)->text()+" In Playlist ");
        return  mPlaylistMap.key( pPlayList->item(mIndex)->text());
}

QString XkPlayListView::PlayListPreFile()
{
      if(mPlaylistMap.isEmpty())
    {
         pLogListView->RootError(" PlayList is empty"); return "NULL";
    }
      int mIndex =  pPlayList->currentRow();
      qDebug()<<"PlayListPreFile current index is "<<mIndex;
          mIndex--;
      if(mIndex < 0) mIndex=0;
      pPlayList->item(mIndex)->setSelected(true);
      pPlayList->setCurrentRow(mIndex);
      pLogListView->RootDebug("Current Row  "+QString::number(mIndex)+" In Playlist ");
      pLogListView->RootInfo("[Play Last Video] "+ pPlayList->item(mIndex)->text()+" In Playlist ");
       return mPlaylistMap.key( pPlayList->item(mIndex)->text());
}

void XkPlayListView::OnRightClicked(QPoint mpos)
{
      QMenu *mRightMenu = new QMenu;
          if(pPlayList->count() >0)
          {
               mRightMenu->addAction(QString("从播放列表删除"),this,SLOT(RemoveFromList()));
               mRightMenu->addAction(QString("保存列表"),this,SLOT(SavePlayList()));
               mRightMenu->addAction(QString("播放"),this,SLOT(OnPlayVideo()));
          }
            mRightMenu->addAction(QString("加载列表"),this,SLOT(LoadPlayList()));
            mRightMenu->exec(QCursor::pos());
}

void XkPlayListView::RemoveFromList()
{
    if(mPlaylistMap.isEmpty()) {   XkLogListView::Instance()->RootError("Play list is empty");   return;  }

        int mIndex =  pPlayList->currentRow();

      QString m_Name_Value =   pPlayList->item(mIndex)->text();//mPlayListItem->text();
      QString m_Path_Key = mPlaylistMap.key(m_Name_Value);
        pPlayList->removeItemWidget(pPlayList->item(mIndex));
          delete pPlayList->item(mIndex);
       mPlaylistMap.remove(m_Path_Key);

      pLogListView->RootInfo("[Remove]  Video "+ m_Name_Value+"From Playlist ");
}

void XkPlayListView::OnPlayVideo()
{

    QString mfilename= mPlaylistMap.key(pPlayList->item(pPlayList->currentRow())->text());
    emit sPlayVideo(mfilename  );
}

void XkPlayListView::SavePlayList()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("Save the Playlist "),"",tr("Playlist File (*.list);;All Files(*)"));

    if(filename.isEmpty()) return;
    else
    {
        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this,tr("unable to open file"),file.errorString());
            return;
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_8);
        out<<mPlaylistMap;
         file.flush();
         file.close();
    }

}

void XkPlayListView::LoadPlayList()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open playlist file"),"",tr("Playlist (*.list);;Allfiles(*)"));
    if(fileName.isEmpty()) return;
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this,tr("unable to open file"),file.errorString());
            return;
        }
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_8);
        mPlaylistMap.clear();
         in>>mPlaylistMap;
    }

    if(mPlaylistMap.isEmpty())
        QMessageBox::information(this,tr("No contents in the file"),tr("The file you opened has no contents"));
    else
    {
        pPlayList->clear();
        QMap<QString,QString>::iterator it;
        for(it=mPlaylistMap.begin();it!=mPlaylistMap.end();++it)
                pPlayList->addItem(it.value());
          pLogListView->RootInfo("Load From the list");
          pPlayList->item(0)->setSelected(true);
          pPlayList->setCurrentRow(0);
    }
}


