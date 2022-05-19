#-------------------------------------------------
#
# Project created by QtCreator 2015-11-21T20:25:11
#
#-------------------------------------------------

QT       += core gui qml quick widgets quickwidgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GFrameSheetViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
win32:RC_ICONS += logo.ico
