QT += core gui

TARGET = Flatty-Dev
TEMPLATE = app

include(../extlibs/QxMesh/QxMesh.pri)
include(../extlibs/QxGraphics/QxGraphics.pri)
include(../extlibs/QxTimeLineEditor/QxTimeLineEditor.pri)

INCLUDEPATH += .

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    timeline/timelineeditor.cpp \
    joint/jointtreeitem.cpp \
    joint/jointgraphicsitem.cpp \
    joint/joint.cpp \
    joint/framedata.cpp \
    joint/animation.cpp \
    timeline/timelinewidget.cpp \
    timeline/timelineheader.cpp \
    timeline/timelinedelegate.cpp

HEADERS += \
    mainwindow.h \
    timeline/timelineeditor.h \
    joint/jointtreeitem.h \
    joint/jointgraphicsitem.h \
    joint/joint.h \
    joint/framedata.h \
    joint/animation.h \
    timeline/timelinewidget.h \
    timeline/timelineheader.h \
    timeline/timelinedelegate.h

FORMS += \
    mainwindow.ui \
    timeline/timelinewidget.ui

RESOURCES += \
    resources/resource.qrc