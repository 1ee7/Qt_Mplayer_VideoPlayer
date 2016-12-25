#ifndef XKVIDEOPLAYER_H
#define XKVIDEOPLAYER_H
#include <QObject>
#include <QProcess>
#include <QTimer>
#include <QFileInfo>
#include "xkloglistview.h"
#include "xkvideowidget.h"
#include "toolsfunc.h"
class XkVideoPlayer : public QObject
{
   Q_OBJECT
private:
     XkVideoPlayer();
public:
   static XkVideoPlayer *Instance();
    void StartPlay(QString);
    void StopOrPlay();
    void ForWardPlay();
    void BackWardPlay();
    void PlayToValue(QString);
public slots:
    void CatchOutPut();
    void QueryVideoInfo();

private:
    QProcess *pVideoProcess;
    QString mPlayerExe;
     QTimer *ptimer;
     bool StartOrStop;

     XkLogListView *pLogListView;
     ToolsFunc *ptoolsfunc;
signals:
      void sPlayOver();
public:
      float mVideoCurTime;
      float mVideoAllTime;
      float mVideoPercent;

};

#endif // XKVIDEOPLAYER_H
