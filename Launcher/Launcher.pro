#-------------------------------------------------
#
# Project created by QtCreator 2015-06-18T13:57:05
#
#-------------------------------------------------

QT   +=  core gui
QT   +=  webkitwidgets network widgets
QT   +=  gui-private
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Launcher
TEMPLATE = app


SOURCES += \
    lutils.cpp \
		lwidgets.cpp \
    lmain.cpp

HEADERS  += \
    lutils.h \
		lwidgets.h \
    lmain.h

DESTDIR = F:/GameTmp

