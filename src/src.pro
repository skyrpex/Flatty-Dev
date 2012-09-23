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
    animation/animation.cpp \
    timeline/timelinewidget.cpp \
    timeline/timelineheader.cpp \
    timeline/timelinedelegate.cpp \
    animation/keyframe.cpp \
    mesh/meshwidget.cpp \
    mathhelper.cpp

HEADERS += \
    mainwindow.h \
    timeline/timelineeditor.h \
    joint/jointtreeitem.h \
    joint/jointgraphicsitem.h \
    joint/joint.h \
    animation/animation.h \
    timeline/timelinewidget.h \
    timeline/timelineheader.h \
    timeline/timelinedelegate.h \
    animation/keyframe.h \
    mesh/meshwidget.h \
    mathhelper.h

FORMS += \
    mainwindow.ui \
    timeline/timelinewidget.ui \
    mesh/meshwidget.ui

RESOURCES += \
    resources/resource.qrc
