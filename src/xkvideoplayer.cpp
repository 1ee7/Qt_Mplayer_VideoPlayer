#include "xkvideoplayer.h"
static XkVideoPlayer * pInstance_VideoPlayer=NULL;
XkVideoPlayer::XkVideoPlayer()
{
    StartOrStop=false;
    mPlayerExe = "/usr/bin/mplayer";
   pVideoProcess = new QProcess();
    ptimer = new QTimer(this);
   connect(ptimer,SIGNAL(timeout()),this,SLOT(QueryVideoInfo()));

    pLogListView = XkLogListView::Instance();

   pVideoProcess->setProcessChannelMode(QProcess::MergedChannels);
      //pVideoProcess->write("hide\n");
   connect(pVideoProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(CatchOutPut()));
   ptoolsfunc=new ToolsFunc();



}

XkVideoPlayer *XkVideoPlayer::Instance()
{
    if( pInstance_VideoPlayer==NULL)
        pInstance_VideoPlayer = new XkVideoPlayer();
    return pInstance_VideoPlayer;
}

void XkVideoPlayer::StartPlay(QString mFileName)
{
     XkLogListView::Instance()->RootInfo("[Start] Play "+QFileInfo(mFileName).baseName());
    pVideoProcess->close();
    QStringList arg1;
    arg1<<mFileName;
    arg1<<"-slave";
    arg1<<"-quiet";
    arg1<<"-zoom";
    arg1<<"-wid"<<QString::number((unsigned int )(XkVideoWidget::Instance()->pVideoWin->winId()));
    pVideoProcess->start(mPlayerExe,arg1);
     pVideoProcess->write("get_time_length\n");
     pVideoProcess->write("get_time_pos\n");
     pVideoProcess->write("get_percent_pos\n");
         ptimer->start(1000);  //1000ms
         XkVideoWidget::Instance()->pVideoSlider->setEnabled(true);

//      connect(pVedioProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(CatchOutPut()));
}

void XkVideoPlayer::StopOrPlay()
{
    pVideoProcess->write("p\n");
    StartOrStop=!StartOrStop;
    if(StartOrStop)
    {      ptimer->stop(); pLogListView->RootInfo("[Halt ]  Play"); }
    else
       {
        pLogListView->RootInfo("[Go On ]  Play");    ptimer->start(1000);  //1000ms
       }
}

void XkVideoPlayer::ForWardPlay()
{
    pVideoProcess->write("seek +10\n");
          StartOrStop=false;
}

void XkVideoPlayer::BackWardPlay()
{
    pVideoProcess->write("seek -10\n");
    StartOrStop=false;
}

void XkVideoPlayer::PlayToValue(QString mvalue)
{
    QString mstr= "seek "+mvalue+" 2\n";
    pVideoProcess->write(mstr.toLocal8Bit().data());

      StartOrStop=false;
}

void XkVideoPlayer::CatchOutPut()
{
     while(pVideoProcess->canReadLine())
    {
           QByteArray buffer(pVideoProcess->readLine());
           if(buffer.startsWith("ANS_TIME_POSITION"))
            {
                 buffer.replace(QByteArray("\n"),QByteArray(""));
                  QString mStr(buffer);
                  mVideoCurTime=mStr.mid(18).toFloat();
                  XkVideoWidget::Instance()->pVideoSlider->setValue(mStr.mid(18).toFloat());
            }
          else if(buffer.startsWith("ANS_LENGTH"))
          {
                 buffer.replace(QByteArray("\n"),QByteArray(""));
                 QString mStr(buffer);
                 mVideoAllTime = mStr.mid(11).toFloat();
                XkVideoWidget::Instance()->pVideoSlider->setRange(0,mStr.mid(11).toFloat());
          }
         else if(buffer.startsWith("ANS_PERCENT_POSITION"))
         {
               buffer.replace(QByteArray("\n"),QByteArray(""));
               QString mStr(buffer);
               XkVideoWidget::Instance()->pPercentLabel->setText(mStr.mid(21)+"%");
          }
    }
}

void XkVideoPlayer::QueryVideoInfo()
{
       pVideoProcess->write("get_time_length\n");
       pVideoProcess->write("get_time_pos\n");
       pVideoProcess->write("get_percent_pos\n");       

       if( mVideoAllTime-2 < mVideoCurTime )
               emit sPlayOver();
               XkVideoWidget::Instance()->pLength->setText(ptoolsfunc->Size2Unit(QString::number(mVideoAllTime)));
               XkVideoWidget::Instance()->pCurTime->setText(ptoolsfunc->Size2Unit(QString::number(mVideoCurTime))+"/");
//             XkVideoWidget::Instance()->pLength->setText(QString("/ %1").arg(mVideoAllTime));
//             XkVideoWidget::Instance()->pCurTime->setText(QString("  %1").arg(mVideoCurTime));
}

