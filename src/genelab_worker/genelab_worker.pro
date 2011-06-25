#-------------------------------------------------
#
# Project created by QtCreator 2011-06-25T20:18:08
#
#-------------------------------------------------

QT       += core testlib network gui

TARGET = genelab_worker
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# genelab core
INCLUDEPATH += \
    ../genelab/core \
    ../genelab/core/engines \
    ../genelab/core/entities \
    ../genelab/core/entities/ui \
    ../genelab/core/factories \
    ../genelab/core/ui \
    ../genelab/core/utils

# genelab apps
INCLUDEPATH += \
    ../genelab/apps/genelab \
    ../genelab/apps/genelab/worker


#library related
INCLUDEPATH  += \
    ../lib/bullet/src \
    ../lib/bullet/Extra/ConvexDecomposition \
    ../lib/qxt/src/core \
    ../lib/qwt/src

QMAKE_CXXFLAGS  += -isystem../lib/bullet/src
QMAKE_CXXFLAGS  += -isystem../lib/bullet/Extra/ConvexDecomposition
QMAKE_CXXFLAGS  += -isystem../lib/qxt/src/core
QMAKE_CXXFLAGS  += -isystem../lib/qwt/src

win32 {
    LIBS += -L../lib/bullet/lib
    LIBS += -L../lib/qxt/lib
    LIBS += -lQxtCore
}

unix {
    LIBS += -framework QxtCore
}

LIBS += -lBulletDynamics
LIBS += -lBulletCollision
LIBS += -lLinearMath
#LIBS += -lConvexDecomposition
#LIBS += -lBulletWorldImporter -lBulletFileLoader
LIBS += -lBulletMultiThreaded
LIBS += -lBulletSoftBody
#LIBS += -lGIMPACTUtils
#LIBS += -lgle
#LIBS += -lglsmap
#LIBS += -lglut32
#LIBS += -lGLUI
#LIBS += -lmui
#LIBS += -lOpenGLSupport

SOURCES += \
    ../genelab/core/engines/simulationmanager.cpp \
    ../genelab/core/engines/events/inputlistener.cpp \
    ../genelab/core/engines/events/eventsmanager.cpp \
    ../genelab/core/engines/engine.cpp \
    ../genelab/core/engines/bullet/bulletengine.cpp \
    ../genelab/core/entities/body/treeshape.cpp \
    ../genelab/core/entities/brain/synapse.cpp \
    ../genelab/core/entities/families/snakefamily.cpp \
    ../genelab/core/entities/brain/sinusin.cpp \
    ../genelab/core/entities/body/fixation.cpp \
    ../genelab/core/entities/entityfamily.cpp \
    ../genelab/core/entities/entity.cpp \
    ../genelab/core/entities/body/bone.cpp \
    ../genelab/core/factories/worldfactory.cpp \
    ../genelab/core/factories/ressources/ressource.cpp \
    ../genelab/core/ui/widgets/entities/generic6dofconstraintcontroller.cpp \
    main.cpp \
    ../genelab/core/engines/bullet/rigidbodyorigin.cpp \
    ../genelab/core/ui/widgets/entities/fixationproperties.cpp \
    ../genelab/core/ui/widgets/entities/bonepropertiescontroller.cpp \
    ../genelab/core/utils/tools.cpp \
    ../genelab/core/engines/bullet/shapes/btshape.cpp \
    ../genelab/core/engines/bullet/shapes/btbox.cpp \
    ../genelab/core/engines/bullet/shapes/btsphere.cpp \
    ../genelab/core/engines/bullet/shapes/btcylinder.cpp \
    ../genelab/core/factories/btshapesfactory.cpp \
    ../genelab/core/entities/families/spider/spider.cpp \
    ../genelab/core/ui/widgets/entities/entitypropertiescontroller.cpp \
    ../genelab/core/engines/bullet/shapes/btbone.cpp \
    ../genelab/core/entities/brain/brainpluggrid.cpp \
    ../genelab/core/entities/brain/brainnode.cpp \
    ../genelab/core/entities/brain/brain.cpp \
    ../genelab/core/entities/brain/brainfunctional.cpp \
    ../genelab/core/entities/brain/brainin.cpp \
    ../genelab/core/entities/brain/brainout.cpp \
    ../genelab/core/ui/widgets/entities/pluggridvisualizer.cpp \
    ../genelab/core/entities/sensors/sensor.cpp \
    ../genelab/core/entities/sensors/positionsensor.cpp \
    ../genelab/core/engines/entities/entitiesengine.cpp \
    ../genelab/core/entities/sensors/gyroscopicsensor.cpp \
    ../genelab/core/entities/sensors/accelerometersensor.cpp \
    ../genelab/core/entities/modifiers/modifier.cpp \
    ../genelab/core/entities/modifiers/rotationalmotorsmodifier.cpp \
    ../genelab/core/factories/ressources/jsonfile.cpp \
    ../genelab/core/factories/ressources/dbrecord.cpp \
    ../genelab/core/entities/families/ant/ant.cpp \
    ../genelab/core/entities/families/genericfamily.cpp \
    ../genelab/core/ui/widgets/entities/pluggriddesignvisualizer.cpp \
    ../genelab/core/world/btworld.cpp \
    ../genelab/core/world/btscene.cpp \
    ../genelab/core/world/btbiome.cpp \
    ../genelab/core/world/spawn.cpp \
    ../genelab/core/factories/btfactory.cpp

HEADERS += \
    ../genelab/core/engines/simulationmanager.h \
    ../genelab/core/engines/events/eventsmanager.h \
    ../genelab/core/engines/engine.h \
    ../genelab/core/engines/bullet/bulletengine.h \
    ../genelab/core/engines/events/inputlistener.h \
    ../genelab/core/entities/body/treeshape.h \
    ../genelab/core/entities/brain/synapse.h \
    ../genelab/core/entities/families/snakefamily.h \
    ../genelab/core/entities/brain/sinusin.h \
    ../genelab/core/entities/body/fixation.h \
    ../genelab/core/entities/entityfamily.h \
    ../genelab/core/entities/entity.h \
    ../genelab/core/entities/body/bone.h \
    ../genelab/core/factories/worldfactory.h \
    ../genelab/core/factories/ressources/ressource.h \
    ../genelab/core/ui/widgets/entities/generic6dofconstraintcontroller.h \
    ../genelab/core/genelabcoreclasses.h \
    ../genelab/core/engines/bullet/rigidbodyorigin.h \
    ../genelab/core/ui/widgets/entities/fixationproperties.h \
    ../genelab/core/ui/widgets/entities/bonepropertiescontroller.h \
    ../genelab/core/utils/tools.h \
    ../genelab/core/engines/bullet/shapes/btshape.h \
    ../genelab/core/engines/bullet/shapes/btbox.h \
    ../genelab/core/engines/bullet/shapes/btsphere.h \
    ../genelab/core/engines/bullet/shapes/btcylinder.h \
    ../genelab/core/factories/btshapesfactory.h \
    ../genelab/core/entities/families/spider/spider.h \
    ../genelab/core/ui/widgets/entities/entitypropertiescontroller.h \
    ../genelab/core/engines/bullet/shapes/btbone.h \
    ../genelab/core/entities/brain/brainpluggrid.h \
    ../genelab/core/entities/brain/brainnode.h \
    ../genelab/core/entities/brain/brain.h \
    ../genelab/core/entities/brain/brainfunctional.h \
    ../genelab/core/entities/brain/brainin.h \
    ../genelab/core/entities/brain/brainout.h \
    ../genelab/core/ui/widgets/entities/pluggridvisualizer.h \
    ../genelab/core/entities/sensors/sensor.h \
    ../genelab/core/entities/sensors/positionsensor.h \
    ../genelab/core/engines/entities/entitiesengine.h \
    ../genelab/core/entities/sensors/gyroscopicsensor.h \
    ../genelab/core/entities/sensors/accelerometersensor.h \
    ../genelab/core/entities/modifiers/modifier.h \
    ../genelab/core/entities/modifiers/rotationalmotorsmodifier.h \
    ../genelab/core/factories/ressources/jsonfile.h \
    ../genelab/core/factories/ressources/dbrecord.h \
    ../genelab/core/entities/families/ant/ant.h \
    ../genelab/core/entities/families/genericfamily.h \
    ../genelab/core/ui/widgets/entities/pluggriddesignvisualizer.h \
    ../genelab/core/ui/widgets/entities/bodyitems.h \
    ../genelab/core/world/btworld.h \
    ../genelab/core/world/btscene.h \
    ../genelab/core/world/btbiome.h \
    ../genelab/core/world/spawn.h \
    ../genelab/core/factories/btfactory.h

FORMS += \
    ../genelab/core/ui/widgets/ogrebulletwindows.ui \
    ../genelab/core/ui/widgets/entities/generic6dofconstraintcontroller.ui \
    ../genelab/core/ui/widgets/entities/fixationproperties.ui \
    ../genelab/core/ui/widgets/entities/bonepropertiescontroller.ui \
    ../genelab/core/ui/widgets/entities/entitypropertiescontroller.ui \

RESOURCES += \
    ../genelab/core/ressources/ressources.qrc
