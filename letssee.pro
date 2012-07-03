#-------------------------------------------------
#
# Project created by QtCreator 2012-05-30T18:47:13
#
#-------------------------------------------------

QT       += core gui webkit sql

TARGET = letssee
TEMPLATE = app

documentation.path = /opt
documentation.files = docs/*
INSTALLS+=documentation
SOURCES += main.cpp\
        mainwindow.cpp \
    webview.cpp \
    cuteurl.cpp \
    tabwidget.cpp \
    searchbar.cpp \
    searchenginebox.cpp \
    historymanager/historymanager.cpp \
    tabbar.cpp

HEADERS  += mainwindow.h \
    webview.h \
    cuteurl.h \
    tabwidget.h \
    searchbar.h \
    searchenginebox.h \
    historymanager/historymanager.h \
    tabbar.h

FORMS    += mainwindow.ui

