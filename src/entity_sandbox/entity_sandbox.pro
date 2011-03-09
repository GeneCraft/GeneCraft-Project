#-------------------------------------------------
#
# Project created by QtCreator 2011-03-09T16:51:38
#
#-------------------------------------------------

QT       += core gui

TARGET = entity_sandbox
TEMPLATE = app

INCLUDEPATH += ../entity

SOURCES += main.cpp\
        entitysandbox.cpp \
    ../entity/entity.cpp \
    ../entity/struct/fixation.cpp \
    ../entity/struct/bone.cpp \
    ../entity/struct/shape.cpp \
    ../entity/struct/treeshape.cpp

HEADERS  += entitysandbox.h \
    ../entity/entity.h \
    ../entity/struct/fixation.h \
    ../entity/struct/bone.h \
    ../entity/struct/shape.h \
    ../entity/struct/treeshape.h

FORMS    += entitysandbox.ui
