#Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud
#
#This file is part of Genecraft-Project.
#
#Genecraft-Project is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#Genecraft-Project is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.

#-------------------------------------------------
#
# Project created by QtCreator 2011-05-16T17:50:27
#
#-------------------------------------------------

QT    += core gui opengl testlib network qml
TARGET = CreatureViewer
TEMPLATE = app
CONFIG += silent

DESTDIR     = ../bin
OBJECTS_DIR = ../obj

include(./genecraft_core.pri)
include(./genecraft_bullet.pri)
include(./genecraft_ui.pri)
include(./genecraft_ogre.pri)


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

