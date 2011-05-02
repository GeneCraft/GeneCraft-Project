#-------------------------------------------------
#
# Project created by QtCreator 2011-05-02T13:17:35
#
#-------------------------------------------------

QT       += core gui

TARGET = brain_sandbox
TEMPLATE = app

INCLUDEPATH += ../


SOURCES += main.cpp\
        brainapp.cpp \
    ../engine/brainengine.cpp \
    ../entity/neural/neuralnetwork.cpp \
    ../factory/neuralnetworkfactory.cpp \
    ../entity/neural/neuralin.cpp \
    ../entity/neural/neuralout.cpp \
    ../engine/engine.cpp \
    ../widget/neuralnetworkvisualizer.cpp \
    ../entity/neural/synapse.cpp \
    ../entity/neural/sinusin.cpp

HEADERS  += brainapp.h \
    ../engine/brainengine.h \
    ../entity/neural/neuralnetwork.h \
    ../factory/neuralnetworkfactory.h \
    ../entity/neural/neuralin.h \
    ../entity/neural/neuralout.h \
    ../engine/engine.h \
    ../classes.h \
    ../widget/neuralnetworkvisualizer.h \
    ../entity/neural/synapse.h \
    ../entity/neural/sinusin.h

FORMS    += brainapp.ui
