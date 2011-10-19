#-------------------------------------------------
#
# Project created by QtCreator 2011-05-16T17:50:27
#
#-------------------------------------------------

QT    += core gui opengl testlib network script webkit
TARGET = CreatureViewer
TEMPLATE = app
CONFIG += silent

DESTDIR     = ../bin
OBJECTS_DIR = ../obj

include(./genecraftcore.pri)
include(./genecraftui.pri)

# genecraft apps
INCLUDEPATH += \
    genecraft/apps/genecraft \
    genecraft/apps/genecraft/creatureviewer \
    genecraft/apps/genecraft/creatureviewer/inputlisteners \

SOURCES += \
    genecraft/apps/genecraft/creatureviewer/ui/creatureviewerwindow.cpp \
    genecraft/apps/genecraft/creatureviewer/ui/creatureviewerabout.cpp \
    genecraft/apps/genecraft/creatureviewer/inputlisteners/creatureviewerinputmanager.cpp \
    genecraft/apps/genecraft/creatureviewer/ui/welcomewidget.cpp \
    creatureviewer/main_cw.cpp

HEADERS += \
    genecraft/apps/genecraft/creatureviewer/ui/creatureviewerwindow.h \
    genecraft/apps/genecraft/creatureviewer/ui/creatureviewerabout.h \
    genecraft/apps/genecraft/creatureviewer/inputlisteners/creatureviewerinputmanager.h \
    genecraft/apps/genecraft/creatureviewer/ui/welcomewidget.h

FORMS += \
    genecraft/apps/genecraft/creatureviewer/ui/creatureviewerwindow.ui \
    genecraft/apps/genecraft/creatureviewer/ui/creatureviewerabout.ui \
    genecraft/apps/genecraft/creatureviewer/ui/welcomewidget.ui

RESOURCES +=


