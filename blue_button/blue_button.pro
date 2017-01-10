#-------------------------------------------------
#
# Project created by QtCreator 2015-04-15T12:34:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = blue_button
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    formabout.cpp \
    connector.cpp \
    controller.cpp \
    formeditor.cpp \
    qlineeditextforkey.cpp \
    filemanager.cpp \
    libloader.cpp

HEADERS  += mainwindow.h \
    formabout.h \
    connector.h \
    controller.h \
    formeditor.h \
    qlineeditextforkey.h \
    filemanager.h \
    libloader.h

FORMS    += mainwindow.ui \
    formabout.ui \
    formeditor.ui

RC_FILE = bb.rc
