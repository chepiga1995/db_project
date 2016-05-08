#-------------------------------------------------
#
# Project created by QtCreator 2016-04-16T08:52:15
#
#-------------------------------------------------
QT       += sql
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = db_project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    skills.cpp

HEADERS  += mainwindow.h \
    login.h \
    skills.h

FORMS    += mainwindow.ui \
    login.ui
