#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QPalette>
#include "xkvideowidget.h"
#include "xkplaylistview.h"
#include "xkvideoplayer.h"
#include "xkfiletreeview.h"
#include "xkpropertytable.h"
#include "xkloglistview.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
    void   CreateActions();
    void   CreateMenuBar();
    void   CreateToolBar();
    void   CreateStatusBar();
    void  CreateDockWidget();
    void  Instance();
private:
    QMenu *pFileMenu;
    QMenu *pOptMenu;
    QMenu *pHelpMenu;

    QAction *pOpenAct;
    QAction *pPlayOrPausAct;
    QAction *pForwardAct;
    QAction *pBackwardAct;
    QAction *pPreListAct;
    QAction *pNextListAct;
    QAction *pExit;

    QToolBar *pToolBar;

public:
    explicit MainWindow(QWidget *parent = 0);

signals:
public slots:
    void OpenFile();
    void OnExit();
    void PauseOrPlay();
    void ForWard();
    void BackWard();
    void VideoSliderMoveTo(int);

    void UpdatePropertyList(QString);
    void PlayVideo(QString);
    void AddFile2List(QString);

    void PlayPreVideo();
    void PlayNextVideo();

    void OnRightClicked(QPoint);
    void FullScreen();
    void NormalScreen();

private:
          XkVideoWidget *pVideoWidget;
          XkVideoPlayer *pVideoPlayer;
          XkFileTreeView *pFileTreeView;
          XkPlayListView *pPlayListView;
          XkPropertyTable *pPropertyTable;
          XkLogListView *pLogListView;

};

#endif // MAINWINDOW_H
