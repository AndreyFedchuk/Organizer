#-------------------------------------------------
#
# Project created by QtCreator 2016-07-22T00:39:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Organizer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tgtablemodel.cpp \
    tgprioritydelegate.cpp \
    dialogaddtarget.cpp \
    tgstatusdelegate.cpp

HEADERS  += mainwindow.h \
    tgtablemodel.h \
    target.h \
    tgprioritydelegate.h \
    dialogaddtarget.h \
    tgstatusdelegate.h

FORMS    += mainwindow.ui \
    dialogaddtarget.ui
