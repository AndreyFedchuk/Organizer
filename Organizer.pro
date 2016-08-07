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
    tgstatusdelegate.cpp \
    setproxyparam.cpp \
    dailytasksmodel.cpp \
    dialogdailytask.cpp \
    dsetting.cpp

HEADERS  += mainwindow.h \
    tgtablemodel.h \
    target.h \
    tgprioritydelegate.h \
    dialogaddtarget.h \
    tgstatusdelegate.h \
    setproxyparam.h \
    dailytasksmodel.h \
    task.h \
    dialogdailytask.h \
    dsetting.h

FORMS    += mainwindow.ui \
    dialogaddtarget.ui \
    setproxyparam.ui \
    dialogdailytask.ui \
    dsetting.ui

RESOURCES += \
    resources.qrc

RC_ICONS = org-2.ico

QMAKE_TARGET_CORPORIGHT = ahudz

VERSION = 0.9.0.0
