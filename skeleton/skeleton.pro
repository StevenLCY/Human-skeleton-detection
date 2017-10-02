#-------------------------------------------------
#
# Project created by QtCreator 2016-12-08T15:22:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = skeleton
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    camera.cpp

HEADERS  += mainwindow.h \
    camera.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$quote(C:\Users\plama\Desktop\opencv\build\include)\
               $$quote(C:\Users\plama\Desktop\opencv\build\include\opencv)\
               $$quote(C:\Users\plama\Desktop\opencv\build\include\opencv2)

LIBS += $$quote(C:\Users\plama\Desktop\opencv\build\x64\vc14\lib\opencv_world310.lib)\
        $$quote(C:\Users\plama\Desktop\opencv\build\x64\vc14\lib\opencv_world310d.lib)

