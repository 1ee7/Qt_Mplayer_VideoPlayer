#include "xkfiletreeview.h"
#include <qdebug.h>

static XkFileTreeView *pInstance_FileTreeView=NULL;

XkFileTreeView::XkFileTreeView(const QString &titleNm, QDockWidget *parent)
    :QDockWidget(titleNm,parent)
{
    mFileNamePath = "NULL";
    mFileTypeList<<"mkv"<<"rmvb"<<"mp4";
    pTreeView = new QTreeView(this) ;
    pFileSystemModel= new QFileSystemModel(this);

    pPlayListView= XkPlayListView::Instance();
            this->setStyleSheet("color:green"); //绿色字体黑色背景

    QWidget* lTitleBar = this->titleBarWidget();
     QWidget* lEmptyWidget = new QWidget();
     this->setTitleBarWidget(lEmptyWidget);
     delete lTitleBar;
}

bool XkFileTreeView::IsPlayFile( )
{
    if(mFileNamePath == "NULL") return false;
    QFileInfo   mFileInfo(mFileNamePath);
   if(mFileInfo.suffix()=="") return false;
    foreach(const QString &str,mFileTypeList)
    {
       if(str.contains(mFileInfo.suffix(),Qt::CaseInsensitive))         return true;
    }
    return false;
}

XkFileTreeView *XkFileTreeView::Instance()
{
    if(pInstance_FileTreeView == NULL)
        pInstance_FileTreeView=new XkFileTreeView(tr("文件目录"));
    return pInstance_FileTreeView;
}

void XkFileTreeView::InitFileTree()
{
    pFileSystemModel->setRootPath(QDir::rootPath());//设置根目录
    pTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
    pTreeView->setModel(pFileSystemModel);
    pTreeView->setRootIndex(pFileSystemModel->index(QDir::rootPath()));   //从模型中找

    pTreeView->header()->hideSection(1);
    pTreeView->header()->hideSection(2);
    pTreeView->header()->hideSection(3);

    this->setWidget(pTreeView);

    connect(pTreeView,  SIGNAL(clicked(QModelIndex)),this, SLOT(OnLeftClicked(const QModelIndex&)));
    connect(pTreeView,  SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(OnRightClicked(const QPoint &)));
}

void XkFileTreeView::OnLeftClicked(const QModelIndex &mIndex)
{
    if (!mIndex.isValid())         return;
     mFileNamePath = pFileSystemModel->filePath(mIndex);
// qDebug()<<"left clicked file"<<mFileNamePath;
     emit sFileTreeLetfClicked(mFileNamePath);
}

void XkFileTreeView::OnRightClicked(const QPoint &)
{
    QModelIndex mIndex = pTreeView->currentIndex();
    if (!mIndex.isValid())           return;
    if(mFileNamePath != pFileSystemModel->filePath(mIndex))
        mFileNamePath = pFileSystemModel->filePath(mIndex);

     QMenu *mRightMenu = new QMenu;
     mRightMenu->addAction(QString("添加到播放列表"),this,SLOT(Add2List()));
     mRightMenu->addAction(QString("播放"),this,SLOT(PlayVideo()));
     mRightMenu->exec(QCursor::pos());
}

void XkFileTreeView::Add2List()
{
    if(IsPlayFile())
     emit sFileTreeAdd2list(mFileNamePath);
}

void XkFileTreeView::PlayVideo()
{
    if(IsPlayFile())
        emit sFileTreePlayVideo(mFileNamePath);
      // 当在文件列表中选中后，在对应的列表中也选中
      if( pPlayListView->mPlaylistMap.contains(mFileNamePath))
   {
               QString mstr = pPlayListView->mPlaylistMap.value(mFileNamePath);
              QListWidgetItem* mItem=   pPlayListView->pPlayList->findItems(mstr,0).at(0);
               pPlayListView->pPlayList->setCurrentItem(mItem,QItemSelectionModel::SelectCurrent);
          //     qDebug()<<"current row"<<pPlayListView->pPlayList->currentRow();
             //  pPlayListView->pPlayList->setCurrentRow();
      }


}






