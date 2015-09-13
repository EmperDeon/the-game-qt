TEMPLATE        = lib
CONFIG         += plugin
CONFIG         += c++11
QT             += webkitwidgets network widgets gui_private
INCLUDEPATH    += ../Global
HEADERS         = \
    mutils.h \
    mparser.h \
    mmodswidget.h \
    mmodloader.h
SOURCES         = \
    mutils.cpp \
    mmodloader.cpp \
    mmodswidget.cpp \
    mparser.cpp
#TARGET          = $$qtLibraryTarget(Global)
TARGET          = base
DESTDIR         = F:/GameTmp/modloaders/

EXAMPLE_FILES = coremod.json
