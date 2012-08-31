#-------------------------------------------------
#
# Project created by QtCreator 2012-05-30T18:47:13
#
#-------------------------------------------------

QT       += core gui webkit sql network

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
    settingseditor.cpp \
    browserapplication.cpp \
    locaionbar.cpp \
    searchenginemanager.cpp \
    cookiejar/cookiejar.cpp \
    suggestcompleter.cpp

HEADERS  += mainwindow.h \
    webview.h \
    cuteurl.h \
    tabwidget.h \
    searchbar.h \
    searchenginebox.h \
    historymanager/historymanager.h \
    settingseditor.h \
    browserapplication.h \
    locaionbar.h \
    searchenginemanager.h \
    cookiejar/cookiejar.h \
    suggestcompleter.h

FORMS    += mainwindow.ui

