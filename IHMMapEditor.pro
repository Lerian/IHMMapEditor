#-------------------------------------------------
#
# Project created by QtCreator 2014-02-08T00:30:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEPENDPATH += forms\
            display
INCLUDEPATH += forms\
            display

TARGET = IHMMapEditor
TEMPLATE = app


SOURCES += main.cpp\
        display/mainwindow.cpp \
    display/homewindow.cpp \
    display/editorwindow.cpp

HEADERS  += display/mainwindow.h \
    display/homewindow.h \
    display/editorwindow.h

FORMS    += forms/mainwindow.ui \
    forms/homewindow.ui \
    forms/editorwindow.ui
