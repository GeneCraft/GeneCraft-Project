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
    ../entity/struct/treeshape.cpp \
    ../entity/struct/shapebuilder.cpp \
    ../entity/struct/lsystem.cpp \
    ../entity/sample/snakebuilder.cpp \
    ../entity/entitybuilder.cpp

HEADERS  += entitysandbox.h \
    ../entity/entity.h \
    ../entity/struct/fixation.h \
    ../entity/struct/bone.h \
    ../entity/struct/shape.h \
    ../entity/struct/treeshape.h \
    ../entity/struct/shapebuilder.h \
    ../entity/struct/lsystem.h \
    ../entity/sample/snakebuilder.h \
    ../entity/entitybuilder.h

FORMS    += entitysandbox.ui
