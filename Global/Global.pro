#-------------------------------------------------
#
# Project created by QtCreator 2015-06-02T22:16:27
#
#-------------------------------------------------

QT       += core gui network
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app
DESTDIR = F:/GameTmp

SOURCES +=\
		gcontainers.cpp \
		gmain.cpp \
		gmods.cpp \
		grender.cpp \
		gutils.cpp \
		gwidgets.cpp

HEADERS  += \
		gheaders.h \
		gcontainers.h \
		gmain.h \
		gmods.h \
		grender.h \
		gutils.h \
		gwidgets.h \
		gmodinterfaces.h
