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
    vacation_type.cpp \
    skill.cpp \
    post.cpp \
    addpost.cpp

HEADERS  += mainwindow.h \
    login.h \
    vacation_type.h \
    skill.h \
    post.h \
    addpost.h

FORMS    += mainwindow.ui \
    login.ui \
    addpost.ui
