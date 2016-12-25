#include "xkvideowidget.h"
#include <qdebug.h>
static XkVideoWidget * pInstance_VideoWidget=NULL;
XkVideoWidget::XkVideoWidget(QWidget *parent) : QWidget(parent)
{
       pVideoWin= new QWidget(this);
        QPalette pal(pVideoWin->palette());
         pal.setColor(QPalette::Background, Qt::black); //设置背景黑色
         pVideoWin->setAutoFillBackground(true);
         pVideoWin->setPalette(pal);

         pVideoSlider = new QSlider(Qt::Horizontal,this);
         pVideoSlider->setEnabled(false);
         pPercentLabel = new QLabel();
         pLength = new QLabel();
         pCurTime = new QLabel();

         QGridLayout *mpVideoLayout = new QGridLayout();
         mpVideoLayout->addWidget(pVideoWin,0,0,1,4);
         mpVideoLayout->addWidget(pVideoSlider,1,0);
         mpVideoLayout->addWidget(pPercentLabel,1,1);
         mpVideoLayout->addWidget(pLength,1,3);
         mpVideoLayout->addWidget(pCurTime,1,2);
         this->setLayout(mpVideoLayout);

}

XkVideoWidget *XkVideoWidget::Instance()
{
    if(pInstance_VideoWidget == NULL)
        pInstance_VideoWidget = new XkVideoWidget();
    return pInstance_VideoWidget;
}

//void XkVideoWidget::OnRightClicked( QPoint mpos)
//{
//    qDebug()<<"dfd";
//    QMenu *mRightMenu = new QMenu;
//    mRightMenu->addAction(QString("全屏"),this,SLOT(FullScreen()));
//    mRightMenu->addAction(QString("退出全屏"),this,SLOT(NormalScreen()));
//    mRightMenu->exec(QCursor::pos());
//}




