#-------------------------------------------------
#
# Project created by QtCreator 2014-02-08T00:30:47
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEPENDPATH += forms\
            display\
            core \
            xml
INCLUDEPATH += forms\
            display\
            core\
            xml

TARGET = IHMMapEditor
TEMPLATE = app


SOURCES += main.cpp\
        display/mainwindow.cpp \
    display/homewindow.cpp \
    display/editorwindow.cpp \
    display/graphitem.cpp \
    display/mapgraphicsview.cpp \
    xml/parser.cpp \
    core/floor.cpp \
    core/node.cpp \
    core/map.cpp

HEADERS  += display/mainwindow.h \
    display/homewindow.h \
    display/editorwindow.h \
    display/graphitem.h \
    display/mapgraphicsview.h \
    xml/parser.h \
    core/floor.h \
    core/node.h \
    core/map.h

FORMS    += forms/mainwindow.ui \
    forms/homewindow.ui \
    forms/editorwindow.ui

RESOURCES += \
    iconsResources.qrc
