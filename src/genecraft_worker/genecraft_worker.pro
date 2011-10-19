    #-------------------------------------------------
#
# Project created by QtCreator 2011-06-25T20:18:08
#
#-------------------------------------------------

QT       += core testlib network gui script

TARGET = genecraft_worker
CONFIG   += console silent
CONFIG   -= app_bundle
#TEMPLATE = app

# genecraft core
INCLUDEPATH += \
    ../genecraft/core \
    ../genecraft/core/engines \
    ../genecraft/core/entities \
    ../genecraft/core/entities/ui \
    ../genecraft/core/factories \
    ../genecraft/core/ui \
    ../genecraft/core/utils

# genecraft apps
INCLUDEPATH += \
    ../genecraft/apps/genecraft \
    ../genecraft/apps/genecraft/worker


#library related
INCLUDEPATH  += \
    ../lib/bullet/src \
    ../lib/bullet/Extra/ConvexDecomposition \
    ../lib/qxt/src/core

QMAKE_CXXFLAGS  += -isystem../lib/bullet/src
QMAKE_CXXFLAGS  += -isystem../lib/bullet/Extra/ConvexDecomposition
QMAKE_CXXFLAGS  += -isystem../lib/qxt/src/core

LIBS += -L../lib/bullet/lib
LIBS += -L../lib/qxt/lib
LIBS += -lQxtCore
LIBS += -lBulletDynamics
LIBS += -lBulletCollision
LIBS += -lLinearMath

SOURCES += \
    ../genecraft/core/engines/engine.cpp \
    ../genecraft/core/engines/events/inputlistener.cpp \
    ../genecraft/core/engines/events/eventsmanager.cpp \
    ../genecraft/core/engines/bullet/bulletengine.cpp \
    ../genecraft/core/engines/bullet/rigidbodyorigin.cpp \
    ../genecraft/core/engines/bullet/shapes/btshape.cpp \
    ../genecraft/core/engines/bullet/shapes/btbox.cpp \
    ../genecraft/core/engines/bullet/shapes/btsphere.cpp \
    ../genecraft/core/engines/bullet/shapes/btcylinder.cpp \
    ../genecraft/core/engines/bullet/shapes/btbone.cpp \
    ../genecraft/core/engines/entities/entitiesengine.cpp \
    ../genecraft/core/entities/entity.cpp \
    ../genecraft/core/entities/entityfamily.cpp \
    ../genecraft/core/entities/body/treeshape.cpp \
    ../genecraft/core/entities/body/bone.cpp \
    ../genecraft/core/entities/body/fixation.cpp \
    ../genecraft/core/entities/families/snakefamily.cpp \
    ../genecraft/core/entities/families/spiderfamily.cpp \
    ../genecraft/core/entities/families/antfamily.cpp \
    ../genecraft/core/entities/families/genericfamily.cpp \
    ../genecraft/core/entities/families/caterpillarfamily.cpp \
    ../genecraft/core/entities/brain/sinusin.cpp \
    ../genecraft/core/entities/brain/brainpluggrid.cpp \
    ../genecraft/core/entities/brain/brainnode.cpp \
    ../genecraft/core/entities/brain/brain.cpp \
    ../genecraft/core/entities/brain/brainfunctional.cpp \
    ../genecraft/core/entities/brain/brainin.cpp \
    ../genecraft/core/entities/brain/brainout.cpp \
    ../genecraft/core/entities/brain/synapse.cpp \
    ../genecraft/core/entities/sensors/sensor.cpp \
    ../genecraft/core/entities/sensors/positionsensor.cpp \
    ../genecraft/core/entities/sensors/gyroscopicsensor.cpp \
    ../genecraft/core/entities/sensors/accelerometersensor.cpp \
    ../genecraft/core/entities/sensors/contactsensor.cpp \
    ../genecraft/core/entities/sensors/boxsmellsensor.cpp \
    ../genecraft/core/entities/sensors/smellsensor.cpp \
    ../genecraft/core/entities/sensors/distancesensor.cpp \
    ../genecraft/core/entities/effectors/effector.cpp \
    ../genecraft/core/entities/effectors/rotationalmotorseffector.cpp \
    ../genecraft/core/entities/effectors/grippereffector.cpp \
    ../genecraft/core/entities/effectors/flyingeffector.cpp \
    ../genecraft/core/entities/statistics/statisticsstorage.cpp \
    ../genecraft/core/entities/statistics/treeshapestats.cpp \
    ../genecraft/core/entities/statistics/statisticsprovider.cpp \
    ../genecraft/core/entities/statistics/fixationstats.cpp \
    ../genecraft/core/entities/mutation/mutationsmanager.cpp \
    ../genecraft/core/entities/mutation/mutation.cpp \
    ../genecraft/core/entities/mutation/floatmutation.cpp \
    ../genecraft/core/entities/mutation/brainnodemutation.cpp \
    ../genecraft/core/entities/mutation/integermutation.cpp \
    ../genecraft/core/entities/mutation/bonelimitsmutation.cpp \
    ../genecraft/core/entities/mutation/simpleprobabilitymutation.cpp \
    ../genecraft/core/entities/mutation/structuralmutation.cpp \
    ../genecraft/core/entities/mutation/structurallist.cpp \
    ../genecraft/core/factories/btshapesfactory.cpp \
    ../genecraft/core/factories/btworldfactory.cpp \
    ../genecraft/core/factories/btfactory.cpp \
    ../genecraft/core/factories/ressources/ressource.cpp \
    ../genecraft/core/factories/ressources/jsonfile.cpp \
    ../genecraft/core/factories/ressources/dbrecord.cpp \
    ../genecraft/core/factories/creaturefactory.cpp \
    ../genecraft/core/world/btworld.cpp \
    ../genecraft/core/world/btscene.cpp \
    ../genecraft/core/world/btbiome.cpp \
    ../genecraft/core/world/spawn.cpp \
    ../genecraft/core/experiment/experiment.cpp \
    ../genecraft/core/experiment/experimentmanager.cpp \
    ../genecraft/core/experiment/result.cpp \
    ../genecraft/core/experiment/resultsmanager.cpp \
    ../genecraft/core/utils/tools.cpp \
    main.cpp \
    ../genecraft/core/ui/widgets/experiments/workerconfiguration.cpp \
    ../genecraft/core/factories/ressources/ressourcesmanager.cpp \
    ../genecraft/core/engines/terrain/terrain.cpp

HEADERS += \
    ../genecraft/core/engines/engine.h \
    ../genecraft/core/engines/events/eventsmanager.h \
    ../genecraft/core/engines/events/inputlistener.h \
    ../genecraft/core/engines/bullet/bulletengine.h \
    ../genecraft/core/engines/bullet/rigidbodyorigin.h \
    ../genecraft/core/engines/bullet/shapes/btshape.h \
    ../genecraft/core/engines/bullet/shapes/btbox.h \
    ../genecraft/core/engines/bullet/shapes/btsphere.h \
    ../genecraft/core/engines/bullet/shapes/btcylinder.h \
    ../genecraft/core/engines/bullet/shapes/btbone.h \
    ../genecraft/core/engines/entities/entitiesengine.h \
    ../genecraft/core/entities/entityfamily.h \
    ../genecraft/core/entities/entity.h \
    ../genecraft/core/entities/body/treeshape.h \
    ../genecraft/core/entities/body/fixation.h \
    ../genecraft/core/entities/body/bone.h \
    ../genecraft/core/entities/brain/synapse.h \
    ../genecraft/core/entities/brain/sinusin.h \
    ../genecraft/core/entities/brain/brainpluggrid.h \
    ../genecraft/core/entities/brain/brainnode.h \
    ../genecraft/core/entities/brain/brain.h \
    ../genecraft/core/entities/brain/brainfunctional.h \
    ../genecraft/core/entities/brain/brainin.h \
    ../genecraft/core/entities/brain/brainout.h \
    ../genecraft/core/entities/sensors/sensor.h \
    ../genecraft/core/entities/sensors/positionsensor.h \
    ../genecraft/core/entities/sensors/gyroscopicsensor.h \
    ../genecraft/core/entities/sensors/accelerometersensor.h \
    ../genecraft/core/entities/sensors/contactsensor.h \
    ../genecraft/core/entities/sensors/boxsmellsensor.h \
    ../genecraft/core/entities/sensors/smellsensor.h \
    ../genecraft/core/entities/sensors/distancesensor.h \
    ../genecraft/core/entities/effectors/effector.h \
    ../genecraft/core/entities/effectors/rotationalmotorseffector.h \
    ../genecraft/core/entities/effectors/grippereffector.h \
    ../genecraft/core/entities/effectors/flyingeffector.h \
    ../genecraft/core/entities/families/antfamily.h \
    ../genecraft/core/entities/families/genericfamily.h \
    ../genecraft/core/entities/families/spiderfamily.h \
    ../genecraft/core/entities/families/snakefamily.h \
    ../genecraft/core/entities/families/caterpillarfamily.h \
    ../genecraft/core/entities/statistics/statisticsstorage.h \
    ../genecraft/core/entities/statistics/treeshapestats.h \
    ../genecraft/core/entities/statistics/statisticsprovider.h \
    ../genecraft/core/entities/statistics/fixationstats.h \
    ../genecraft/core/entities/mutation/mutationsmanager.h \
    ../genecraft/core/entities/mutation/mutation.h \
    ../genecraft/core/entities/mutation/floatmutation.h \
    ../genecraft/core/entities/mutation/brainnodemutation.h \
    ../genecraft/core/entities/mutation/integermutation.h \
    ../genecraft/core/entities/mutation/bonelimitsmutation.h \
    ../genecraft/core/entities/mutation/simpleprobabilitymutation.h \
    ../genecraft/core/entities/mutation/structuralmutation.h \
    ../genecraft/core/entities/mutation/structurallist.h \
    ../genecraft/core/factories/btworldfactory.h \
    ../genecraft/core/factories/ressources/ressource.h \
    ../genecraft/core/factories/btfactory.h \
    ../genecraft/core/factories/ressources/jsonfile.h \
    ../genecraft/core/factories/ressources/dbrecord.h \
    ../genecraft/core/factories/btshapesfactory.h \
    ../genecraft/core/factories/creaturefactory.h \
    ../genecraft/core/world/btworld.h \
    ../genecraft/core/world/btscene.h \
    ../genecraft/core/world/btbiome.h \
    ../genecraft/core/world/spawn.h \
    ../genecraft/core/experiment/experiment.h \
    ../genecraft/core/experiment/experimentmanager.h \
    ../genecraft/core/experiment/result.h \
    ../genecraft/core/experiment/resultsmanager.h \
    ../genecraft/core/utils/tools.h \
    ../genecraft/core/genecraftcoreclasses.h \
    ../genecraft/core/ui/widgets/experiments/workerconfiguration.h \
    ../genecraft/core/factories/ressources/ressourcesmanager.h \
    ../genecraft/core/engines/terrain/terrain.h


RESOURCES += \
    ../genecraft/core/ressources/ressources.qrc

FORMS += \
    ../genecraft/core/ui/widgets/experiments/workerconfiguration.ui
