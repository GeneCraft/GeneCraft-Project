    #-------------------------------------------------
#
# Project created by QtCreator 2011-06-25T20:18:08
#
#-------------------------------------------------

QT       += core testlib network gui script

TARGET = genecraft_worker
CONFIG   += console silent
CONFIG   -= app_bundle

DEFINES += WORKER

DESTDIR     = ../bin
OBJECTS_DIR = ../obj


include(./genecraft_bullet.pri)
include(./genecraft_core.pri)

INCLUDEPATH += genecraft/core/ui

SOURCES += \
    genecraft/core/ui/widgets/experiments/workerconfiguration.cpp \
    worker/main_wo.cpp

HEADERS += \
    genecraft/core/ui/widgets/experiments/workerconfiguration.h

RESOURCES += \
    genecraft/core/ressources/ressources.qrc

FORMS += \
    genecraft/core/ui/widgets/experiments/workerconfiguration.ui




