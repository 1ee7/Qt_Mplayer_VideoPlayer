#ifndef XKVIDEOWIDGET_H
#define XKVIDEOWIDGET_H
#include  <QWidget>
#include  <QLabel>
#include <QSlider>
#include <QGridLayout>
#include <QMenu>

class XkVideoWidget : public QWidget
{
    Q_OBJECT
private:
    explicit XkVideoWidget(QWidget *parent = 0);

public:
     static XkVideoWidget *Instance();
signals:

public slots:
//      void OnRightClicked( QPoint );
public:
         QWidget  *pVideoWin;
         QSlider     *pVideoSlider;
         QLabel      *pPercentLabel;
         QLabel      *pLength;
         QLabel      *pCurTime;

private:

};

#endif // XKVIDEOWIDGET_H
