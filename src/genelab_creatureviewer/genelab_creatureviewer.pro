#-------------------------------------------------
#
# Project created by QtCreator 2011-05-15T19:22:29
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = genelab_creatureviewer
TEMPLATE = app

SOURCES += main.cpp\
    ../genelab/core/engine/ogremanager.cpp \
    ../genelab/core/engine/eventmanager.cpp \
    ../genelab/core/engine/engine.cpp \
    ../genelab/core/engine/bulletmanager.cpp \
    ../genelab/core/engine/brainengine.cpp \
    ../genelab/core/engine/input/ogrefreecamera.cpp \
    ../genelab/core/engine/input/inputlistener.cpp \
    ../genelab/core/engine/input/creatureviewerinputmanager.cpp \
    ../genelab/core/entity/ogrebulletentityfamily.cpp \
    ../genelab/core/entity/ogrebulletentity.cpp \
    ../genelab/core/entity/entityfamily.cpp \
    ../genelab/core/entity/entity.cpp \
    ../genelab/core/entity/neural/synapse.cpp \
    ../genelab/core/entity/neural/neuralin.cpp \
    ../genelab/core/entity/neural/neuralout.cpp \
    ../genelab/core/entity/neural/sinusin.cpp \
    ../genelab/core/entity/neural/neuralnetwork.cpp \
    ../genelab/core/entity/sample/snakefamily.cpp \
    ../genelab/core/entity/struct/treeshape.cpp \
    ../genelab/core/entity/struct/fixation.cpp \
    ../genelab/core/entity/struct/articulatedbone.cpp \
    ../genelab/core/factory/worldfactory.cpp \
    ../genelab/core/factory/ressource.cpp \
    ../genelab/core/factory/neuralnetworkfactory.cpp \
    ../genelab/core/factory/mainfactory.cpp \
    ../genelab/core/factory/jsonloader.cpp \
    ../genelab/core/factory/entityfactory.cpp \
    ../genelab/core/factory/enginefactory.cpp \
    ../genelab/core/simulation/simulationmanager.cpp \
    ../genelab/core/utils/sandboxtools.cpp \
    ../genelab/core/world/world.cpp \
    ../genelab/ui/ogrebulletwindows.cpp \
    ../genelab/ui/widget/neuralnetworkvisualizer.cpp \
    ../genelab/ui/widget/generic6dofconstraintcontroller.cpp \
    ../genelab/ui/widget/ogrewidget.cpp \
    ../genelab/core/world/ogrebulletworld.cpp

HEADERS  += \
    ../genelab/classes.h \
    ../genelab/core/engine/ogremanager.h \
    ../genelab/core/engine/eventmanager.h \
    ../genelab/core/engine/engine.h \
    ../genelab/core/engine/bulletmanager.h \
    ../genelab/core/engine/brainengine.h \
    ../genelab/core/engine/input/ogrefreecamera.h \
    ../genelab/core/engine/input/inputlistener.h \
    ../genelab/core/engine/input/creatureviewerinputmanager.h \
    ../genelab/core/entity/ogrebulletentityfamily.h \
    ../genelab/core/entity/ogrebulletentity.h \
    ../genelab/core/entity/entityfamily.h \
    ../genelab/core/entity/entity.h \
    ../genelab/core/entity/neural/sinusin.h \
    ../genelab/core/entity/neural/neuralin.h \
    ../genelab/core/entity/neural/neuralout.h \
    ../genelab/core/entity/neural/neuralnetwork.h \
    ../genelab/core/entity/neural/synapse.h \
    ../genelab/core/entity/sample/snakefamily.h \
    ../genelab/core/entity/struct/types.h \
    ../genelab/core/entity/struct/treeshape.h \
    ../genelab/core/entity/struct/fixation.h \
    ../genelab/core/entity/struct/articulatedbone.h \
    ../genelab/core/factory/worldfactory.h \
    ../genelab/core/factory/ressource.h \
    ../genelab/core/factory/neuralnetworkfactory.h \
    ../genelab/core/factory/mainfactory.h \
    ../genelab/core/factory/jsonloader.h \
    ../genelab/core/factory/entityfactory.h \
    ../genelab/core/factory/enginefactory.h \
    ../genelab/core/simulation/simulationmanager.h \
    ../genelab/core/utils/sandboxtools.h \
    ../genelab/core/world/world.h \
    ../genelab/ui/ogrebulletwindows.h \
    ../genelab/ui/widget/neuralnetworkvisualizer.h \
    ../genelab/ui/widget/generic6dofconstraintcontroller.h \
    ../genelab/ui/widget/ogrewidget.h \
    ../genelab/core/world/ogrebulletworld.h

FORMS    += \
    ../genelab/ui/ogrebulletwindows.ui \
    ../genelab/ui/widget/generic6dofconstraintcontroller.ui


#genelab
INCLUDEPATH += ../genelab/

#library related

#CONFIG(Debug) {
    QMAKE_CXXFLAGS  += -isystem../lib/ogre/include/OGRE
    QMAKE_CXXFLAGS  += -isystem../lib/ogre/include/OIS
    QMAKE_CXXFLAGS  += -isystem../lib/ogre/include
    QMAKE_CXXFLAGS  += -isystem../lib/ogre/boost_1_44
    QMAKE_CXXFLAGS  += -isystem../lib/ogrebullet-build/include/Collisions
    QMAKE_CXXFLAGS  += -isystem../lib/ogrebullet-build/include/Dynamics
    QMAKE_CXXFLAGS  += -isystem../lib/ogrebullet-build/include
    QMAKE_CXXFLAGS  += -isystem../lib/bullet/src
    QMAKE_CXXFLAGS  += -isystem../lib/bullet/Extra/ConvexDecomposition
    QMAKE_CXXFLAGS  += -isystem../lib/qxt/src/core/
#}

#library related
INCLUDEPATH  += ../lib/ogre/include/OGRE
INCLUDEPATH  += ../lib/ogre/include/OIS
INCLUDEPATH  += ../lib/ogre/include
INCLUDEPATH  += ../lib/ogre/boost_1_44
INCLUDEPATH  += ../lib/ogrebullet-build/include/Collisions
INCLUDEPATH  += ../lib/ogrebullet-build/include/Dynamics
INCLUDEPATH  += ../lib/ogrebullet-build/include
INCLUDEPATH  += ../lib/bullet/src
INCLUDEPATH  += ../lib/bullet/Extra/ConvexDecomposition
INCLUDEPATH  += ../lib/qxt/src/core/


CONFIG(Debug) {
    LIBS += -L../lib/ogre/bin/debug
    LIBS += -lOgreMain_d -lOIS_d
}
CONFIG(Release) {
    LIBS += -L../lib/ogre/bin/release
    LIBS += -lOgreMain -lOIS
}

LIBS += -L../lib/ogrebullet-build/lib
LIBS += -L../lib/bullet/lib
LIBS += -L../lib/qxt/lib

LIBS += -lQxtCore
LIBS += -lOgreBulletCol -lOgreBulletDyn
LIBS += -lBulletDynamics
LIBS += -lBulletCollision
LIBS += -lLinearMath
LIBS += -lConvexDecomposition
LIBS += -lBulletWorldImporter -lBulletFileLoader
LIBS += -lBulletMultiThreaded
LIBS += -lBulletSoftBody
LIBS += -lGIMPACTUtils
#LIBS += -lgle
#LIBS += -lglsmap
#LIBS += -lglut32
LIBS += -lGLUI
LIBS += -lMiniCL
#LIBS += -lmui
LIBS += -lOpenGLSupport
