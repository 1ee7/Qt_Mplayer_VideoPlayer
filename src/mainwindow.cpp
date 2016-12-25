#include "mainwindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
        Instance();

        CreateActions();
        CreateMenuBar();
        CreateToolBar();
        CreateStatusBar();
        CreateDockWidget();

        connect(XkFileTreeView::Instance(),SIGNAL(sFileTreeLetfClicked(QString)),this,SLOT(UpdatePropertyList(QString))) ;
        connect(XkFileTreeView::Instance(),SIGNAL(sFileTreePlayVideo(QString)),this,SLOT(PlayVideo(QString))) ;
        connect(XkFileTreeView::Instance(),SIGNAL(sFileTreeAdd2list(QString)),this,SLOT(AddFile2List(QString))) ;
        connect(XkPlayListView::Instance(),SIGNAL(sPlayVideo(QString)),this,SLOT(PlayVideo(QString)));
        connect(XkVideoPlayer::Instance(),SIGNAL(sPlayOver()),this,SLOT(PlayNextVideo()));
        connect(XkVideoWidget::Instance()->pVideoSlider,SIGNAL(sliderMoved(int)),this,SLOT(VideoSliderMoveTo(int)));
//        this->setStyleSheet("color:green;background-color:black;"); //绿色字体黑色背景

}

void MainWindow::Instance()
{
    setWindowState(Qt::WindowMaximized);

    pVideoWidget = XkVideoWidget::Instance();
    setCentralWidget(pVideoWidget);
    //添加右键
    pVideoWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(pVideoWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(OnRightClicked(QPoint)));

    pVideoPlayer = XkVideoPlayer::Instance();
}

void MainWindow::CreateActions()
{
      pOpenAct = new QAction(tr("OPen"),this);
      pOpenAct->setStatusTip(tr("Open a vedio file"));
      connect(pOpenAct,SIGNAL(triggered()),this,SLOT(OpenFile()));

      pExit = new QAction(tr("退出"),this);
      connect(pExit,SIGNAL(triggered()),this,SLOT(OnExit()));

     pPlayOrPausAct = new QAction(tr("暂停/ 播放"),this);
     connect(pPlayOrPausAct,SIGNAL(triggered()),this,SLOT(PauseOrPlay()));

     pForwardAct = new QAction(tr("前进"),this);
     connect(pForwardAct,SIGNAL(triggered()), this, SLOT(ForWard()));

     pBackwardAct = new QAction(tr("后退"),this);
     connect(pBackwardAct,SIGNAL(triggered()),this,SLOT(BackWard()));

     pPreListAct = new QAction(tr("上一个"),this);
     connect(pPreListAct,SIGNAL(triggered()),this,SLOT(PlayPreVideo()));

     pNextListAct = new QAction(tr("下一个"),this);
      connect(pNextListAct,SIGNAL(triggered()),this,SLOT(PlayNextVideo()));
}

void MainWindow::CreateMenuBar()
{
       pFileMenu = menuBar()->addMenu(tr("文件"));
              pFileMenu->addAction(pOpenAct);
              pFileMenu->addSeparator();
              pFileMenu->addAction(pExit);

          pOptMenu = menuBar()->addMenu(tr("选项"));
             pOptMenu->addAction(pPlayOrPausAct);
             pOptMenu->addAction(pForwardAct);
             pOptMenu->addAction(pBackwardAct);

         pHelpMenu = menuBar()->addMenu(tr("帮助"));
}

void MainWindow::CreateToolBar()
{
       pToolBar = addToolBar(tr("&Opt"));
        pToolBar ->addAction(pPlayOrPausAct);
        pToolBar->addAction(pForwardAct);
        pToolBar ->addAction(pBackwardAct);
        pToolBar->addAction(pPreListAct);
        pToolBar ->addAction(pNextListAct);
}

void MainWindow::CreateStatusBar()
{
      statusBar()->showMessage(tr("Ready"));
}

void MainWindow::CreateDockWidget()
{
    pFileTreeView = XkFileTreeView::Instance();
    pFileTreeView->InitFileTree();
    addDockWidget( Qt::LeftDockWidgetArea,pFileTreeView);

     pPlayListView = XkPlayListView::Instance();
     pPlayListView->InitListView();
     addDockWidget(Qt::LeftDockWidgetArea,pPlayListView);

     pPropertyTable  = new XkPropertyTable(tr("文件属性"));
     pPropertyTable->InitPropertyTable();
      addDockWidget(Qt::LeftDockWidgetArea,pPropertyTable);

      pLogListView =  XkLogListView::Instance();
      pLogListView->InitLogView();
      addDockWidget(Qt::BottomDockWidgetArea,pLogListView);

     QMainWindow::tabifyDockWidget(pPlayListView,pFileTreeView);
      QMainWindow::setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
}


void MainWindow::OpenFile()
{
    QString mFileName = QFileDialog::getOpenFileName(this,tr("open file "),"/home/tgl/","(*.mkv *.mp4 *.rmvb)");
    qDebug()<<"open file name is "<<mFileName;
    pVideoPlayer->StartPlay(mFileName);
}

void MainWindow::OnExit()
{
    exit(1);
}

void MainWindow::PauseOrPlay()
{
    pVideoPlayer->StopOrPlay();
}

void MainWindow::ForWard()
{
    pVideoPlayer->ForWardPlay();
}

void MainWindow::BackWard()
{
    pVideoPlayer->BackWardPlay();
}

void MainWindow::UpdatePropertyList(QString mfilename)
{
    pPropertyTable->UpdateFileProperty(mfilename);
}

void MainWindow::PlayVideo(QString mfilename)
{
  pVideoPlayer->StartPlay(mfilename);
}

void MainWindow::AddFile2List(QString mfilename)
{
    pPlayListView->AddItem(mfilename);
}

void MainWindow::PlayPreVideo()
{
    QString filename = pPlayListView->PlayListPreFile();
    if( filename == "NULL") return;
       pVideoPlayer->StartPlay(filename);
  }

void MainWindow::PlayNextVideo()
{
       QString filename = pPlayListView->PlayListNextFile();
     if(filename== "NULL") return;
     pVideoPlayer->StartPlay(filename);
}

void MainWindow::OnRightClicked(QPoint)
{
        QMenu *mRightMenu = new QMenu;
        mRightMenu->addAction(QString("全屏"),this,SLOT(FullScreen()));
        mRightMenu->addAction(QString("退出全屏"),this,SLOT(NormalScreen()));
        mRightMenu->exec(QCursor::pos());
}

void MainWindow::FullScreen()
{
    pLogListView->hide();
    pFileTreeView->hide();
    pPlayListView->hide();
    pPropertyTable->hide();
    pToolBar->hide();
   menuBar()->hide();
   statusBar()->hide();

    this->showFullScreen();
        pVideoWidget->pVideoSlider->hide();
       pVideoWidget->pPercentLabel->hide();
       pVideoWidget->pCurTime->hide();
       pVideoWidget->pLength->hide();
    pVideoWidget->pVideoWin->showFullScreen();
}

void MainWindow::NormalScreen()
{
    pLogListView->show();
    pFileTreeView->show();
    pPlayListView->show();
    pPropertyTable->show();
    pToolBar->show();
    menuBar()->show();
    statusBar()->show();
    pVideoWidget->pVideoWin->showNormal();
    pVideoWidget->pVideoSlider->show();
    pVideoWidget->pPercentLabel->show();
    pVideoWidget->pCurTime->show();
    pVideoWidget->pLength->show();
}

void MainWindow::VideoSliderMoveTo(int mvalue)
{
    int mSliderValue = mvalue*pVideoPlayer->mVideoAllTime/pVideoWidget->pVideoSlider->maximum();
    QString mstr=QString::number(mSliderValue);
    pVideoPlayer->PlayToValue(mstr);
        pLogListView->RootInfo("Slide to "+mstr);
}
