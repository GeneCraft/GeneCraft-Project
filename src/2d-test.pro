#-------------------------------------------------
#
# Project created by QtCreator 2011-05-16T17:50:27
#
#-------------------------------------------------

QT    += core gui opengl testlib network script webkit
TARGET = 2D-test
TEMPLATE = app
CONFIG += silent

DESTDIR     = ../bin
OBJECTS_DIR = ../obj

include(./genecraft_core.pri)
include(./genecraft_chipmunk.pri)

SOURCES += \
    2d-test/main.cpp

RESOURCES +=

