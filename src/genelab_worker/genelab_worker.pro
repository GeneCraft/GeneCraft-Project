#-------------------------------------------------
#
# Project created by QtCreator 2011-06-25T20:18:08
#
#-------------------------------------------------

QT       += core testlib network gui script

TARGET = genecraft_worker
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
    ../lib/qxt/src/core

QMAKE_CXXFLAGS  += -isystem../lib/bullet/src
QMAKE_CXXFLAGS  += -isystem../lib/bullet/Extra/ConvexDecomposition
QMAKE_CXXFLAGS  += -isystem../lib/qxt/src/core

#win32 {
    LIBS += -L../lib/bullet/lib
    LIBS += -L../lib/qxt/lib
    LIBS += -lQxtCore
#}

unix {
#    LIBS += -L/usr/local/Qxt/lib
#    LIBS += -lQxtCore
}
LIBS += -lBulletDynamics
LIBS += -lBulletCollision
LIBS += -lLinearMath
#LIBS += -lConvexDecomposition
#LIBS += -lBulletWorldImporter -lBulletFileLoader
#LIBS += -lBulletMultiThreaded
#LIBS += -lBulletSoftBody
#LIBS += -lGIMPACTUtils
#LIBS += -lgle
#LIBS += -lglsmap
#LIBS += -lglut32
#LIBS += -lGLUI
#LIBS += -lmui
#LIBS += -lOpenGLSupport

SOURCES += \
    ../genelab/core/engines/engine.cpp \
    ../genelab/core/engines/simulationmanager.cpp \
    ../genelab/core/engines/events/inputlistener.cpp \
    ../genelab/core/engines/events/eventsmanager.cpp \
    ../genelab/core/engines/bullet/bulletengine.cpp \
    ../genelab/core/engines/bullet/rigidbodyorigin.cpp \
    ../genelab/core/engines/bullet/shapes/btshape.cpp \
    ../genelab/core/engines/bullet/shapes/btbox.cpp \
    ../genelab/core/engines/bullet/shapes/btsphere.cpp \
    ../genelab/core/engines/bullet/shapes/btcylinder.cpp \
    ../genelab/core/engines/bullet/shapes/btbone.cpp \
    ../genelab/core/engines/entities/entitiesengine.cpp \
    ../genelab/core/entities/entity.cpp \
    ../genelab/core/entities/entityfamily.cpp \
    ../genelab/core/entities/body/treeshape.cpp \
    ../genelab/core/entities/body/bone.cpp \
    ../genelab/core/entities/body/fixation.cpp \
    ../genelab/core/entities/families/snakefamily.cpp \
    ../genelab/core/entities/families/spiderfamily.cpp \
    ../genelab/core/entities/families/antfamily.cpp \
    ../genelab/core/entities/families/genericfamily.cpp \
    ../genelab/core/entities/families/caterpillarfamily.cpp \
    ../genelab/core/entities/brain/sinusin.cpp \
    ../genelab/core/entities/brain/brainpluggrid.cpp \
    ../genelab/core/entities/brain/brainnode.cpp \
    ../genelab/core/entities/brain/brain.cpp \
    ../genelab/core/entities/brain/brainfunctional.cpp \
    ../genelab/core/entities/brain/brainin.cpp \
    ../genelab/core/entities/brain/brainout.cpp \
    ../genelab/core/entities/brain/synapse.cpp \
    ../genelab/core/entities/sensors/sensor.cpp \
    ../genelab/core/entities/sensors/positionsensor.cpp \
    ../genelab/core/entities/sensors/gyroscopicsensor.cpp \
    ../genelab/core/entities/sensors/accelerometersensor.cpp \
    ../genelab/core/entities/sensors/contactsensor.cpp \
    ../genelab/core/entities/sensors/boxsmellsensor.cpp \
    ../genelab/core/entities/sensors/smellsensor.cpp \
    ../genelab/core/entities/sensors/distancesensor.cpp \
    ../genelab/core/entities/effectors/effector.cpp \
    ../genelab/core/entities/effectors/rotationalmotorseffector.cpp \
    ../genelab/core/entities/effectors/grippereffector.cpp \
    ../genelab/core/entities/effectors/flyingeffector.cpp \
    ../genelab/core/entities/statistics/statisticsstorage.cpp \
    ../genelab/core/entities/statistics/treeshapestats.cpp \
    ../genelab/core/entities/statistics/statisticsprovider.cpp \
    ../genelab/core/entities/statistics/fixationstats.cpp \
    ../genelab/core/entities/mutation/mutationsmanager.cpp \
    ../genelab/core/entities/mutation/mutation.cpp \
    ../genelab/core/entities/mutation/floatmutation.cpp \
    ../genelab/core/entities/mutation/brainnodemutation.cpp \
    ../genelab/core/entities/mutation/integermutation.cpp \
    ../genelab/core/entities/mutation/bonelimitsmutation.cpp \
    ../genelab/core/entities/mutation/simpleprobabilitymutation.cpp \
    ../genelab/core/entities/mutation/structuralmutation.cpp \
    ../genelab/core/entities/mutation/structurallist.cpp \
    ../genelab/core/factories/btshapesfactory.cpp \
    ../genelab/core/factories/btworldfactory.cpp \
    ../genelab/core/factories/btfactory.cpp \
    ../genelab/core/factories/ressources/ressource.cpp \
    ../genelab/core/factories/ressources/jsonfile.cpp \
    ../genelab/core/factories/ressources/dbrecord.cpp \
    ../genelab/core/factories/creaturefactory.cpp \
    ../genelab/core/ui/widgets/entities/pluggridvisualizer.cpp \
    ../genelab/core/ui/widgets/entities/pluggriddesignvisualizer.cpp \
    ../genelab/core/world/btworld.cpp \
    ../genelab/core/world/btscene.cpp \
    ../genelab/core/world/btbiome.cpp \
    ../genelab/core/world/spawn.cpp \
    ../genelab/core/experiment/experiment.cpp \
    ../genelab/core/experiment/experimentmanager.cpp \
    ../genelab/core/experiment/result.cpp \
    ../genelab/core/experiment/resultsmanager.cpp \
    ../genelab/core/utils/tools.cpp \
    main.cpp \
    ../genelab/core/ui/widgets/experiments/workerconfiguration.cpp \
    ../genelab/core/factories/ressources/ressourcesmanager.cpp

HEADERS += \
    ../genelab/core/engines/engine.h \
    ../genelab/core/engines/simulationmanager.h \
    ../genelab/core/engines/events/eventsmanager.h \
    ../genelab/core/engines/events/inputlistener.h \
    ../genelab/core/engines/bullet/bulletengine.h \
    ../genelab/core/engines/bullet/rigidbodyorigin.h \
    ../genelab/core/engines/bullet/shapes/btshape.h \
    ../genelab/core/engines/bullet/shapes/btbox.h \
    ../genelab/core/engines/bullet/shapes/btsphere.h \
    ../genelab/core/engines/bullet/shapes/btcylinder.h \
    ../genelab/core/engines/bullet/shapes/btbone.h \
    ../genelab/core/engines/entities/entitiesengine.h \
    ../genelab/core/entities/entityfamily.h \
    ../genelab/core/entities/entity.h \
    ../genelab/core/entities/body/treeshape.h \
    ../genelab/core/entities/body/fixation.h \
    ../genelab/core/entities/body/bone.h \
    ../genelab/core/entities/brain/synapse.h \
    ../genelab/core/entities/brain/sinusin.h \
    ../genelab/core/entities/brain/brainpluggrid.h \
    ../genelab/core/entities/brain/brainnode.h \
    ../genelab/core/entities/brain/brain.h \
    ../genelab/core/entities/brain/brainfunctional.h \
    ../genelab/core/entities/brain/brainin.h \
    ../genelab/core/entities/brain/brainout.h \
    ../genelab/core/entities/sensors/sensor.h \
    ../genelab/core/entities/sensors/positionsensor.h \
    ../genelab/core/entities/sensors/gyroscopicsensor.h \
    ../genelab/core/entities/sensors/accelerometersensor.h \
    ../genelab/core/entities/sensors/contactsensor.h \
    ../genelab/core/entities/sensors/boxsmellsensor.h \
    ../genelab/core/entities/sensors/smellsensor.h \
    ../genelab/core/entities/sensors/distancesensor.h \
    ../genelab/core/entities/effectors/effector.h \
    ../genelab/core/entities/effectors/rotationalmotorseffector.h \
    ../genelab/core/entities/effectors/grippereffector.h \
    ../genelab/core/entities/effectors/flyingeffector.h \
    ../genelab/core/entities/families/antfamily.h \
    ../genelab/core/entities/families/genericfamily.h \
    ../genelab/core/entities/families/spiderfamily.h \
    ../genelab/core/entities/families/snakefamily.h \
    ../genelab/core/entities/families/caterpillarfamily.h \
    ../genelab/core/entities/statistics/statisticsstorage.h \
    ../genelab/core/entities/statistics/treeshapestats.h \
    ../genelab/core/entities/statistics/statisticsprovider.h \
    ../genelab/core/entities/statistics/fixationstats.h \
    ../genelab/core/entities/mutation/mutationsmanager.h \
    ../genelab/core/entities/mutation/mutation.h \
    ../genelab/core/entities/mutation/floatmutation.h \
    ../genelab/core/entities/mutation/brainnodemutation.h \
    ../genelab/core/entities/mutation/integermutation.h \
    ../genelab/core/entities/mutation/bonelimitsmutation.h \
    ../genelab/core/entities/mutation/simpleprobabilitymutation.h \
    ../genelab/core/entities/mutation/structuralmutation.h \
    ../genelab/core/entities/mutation/structurallist.h \
    ../genelab/core/factories/btworldfactory.h \
    ../genelab/core/factories/ressources/ressource.h \
    ../genelab/core/factories/btfactory.h \
    ../genelab/core/factories/ressources/jsonfile.h \
    ../genelab/core/factories/ressources/dbrecord.h \
    ../genelab/core/factories/btshapesfactory.h \
    ../genelab/core/factories/creaturefactory.h \
    ../genelab/core/ui/widgets/entities/pluggridvisualizer.h \
    ../genelab/core/ui/widgets/entities/pluggriddesignvisualizer.h \
    ../genelab/core/world/btworld.h \
    ../genelab/core/world/btscene.h \
    ../genelab/core/world/btbiome.h \
    ../genelab/core/world/spawn.h \
    ../genelab/core/experiment/experiment.h \
    ../genelab/core/experiment/experimentmanager.h \
    ../genelab/core/experiment/result.h \
    ../genelab/core/experiment/resultsmanager.h \
    ../genelab/core/utils/tools.h \
    ../genelab/core/genecraftcoreclasses.h \
    ../genelab/core/ui/widgets/experiments/workerconfiguration.h \
    ../genelab/core/factories/ressources/ressourcesmanager.h


RESOURCES += \
    ../genelab/core/ressources/ressources.qrc

FORMS += \
    ../genelab/core/ui/widgets/experiments/workerconfiguration.ui
