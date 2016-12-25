#include <QApplication>
#include <QTextCodec>
#include "mainwindow.h"
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(5,5,1)
    QTextCodec* codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForTr(codec);
    QByteArray name = QTextCodec::codecForLocale()->name();
    QTextCodec::setCodecForLocale(codec);
    name = QTextCodec::codecForLocale()->name();
    QTextCodec::setCodecForCStrings(codec);
   #endif

    QApplication app(argc,argv);

    MainWindow Win;
    Win.show();

    app.exec();
}
