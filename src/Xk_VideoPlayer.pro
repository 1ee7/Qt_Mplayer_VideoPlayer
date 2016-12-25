QT += widgets
HEADERS += \
    mainwindow.h \
    xkvideowidget.h \
    xkvideoplayer.h \
    xkfiletreeview.h \
    xkplaylistview.h \
    xkpropertytable.h \
    xkloglistview.h \
    toolsfunc.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    xkvideowidget.cpp \
    xkvideoplayer.cpp \
    xkfiletreeview.cpp \
    xkplaylistview.cpp \
    xkpropertytable.cpp \
    xkloglistview.cpp \
    toolsfunc.cpp

#unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/ -llog4cpp

#INCLUDEPATH += $$PWD/../../../../../usr/local/include
#DEPENDPATH += $$PWD/../../../../../usr/local/include
