#-------------------------------------------------
#
# Project created by QtCreator 2011-05-16T17:50:27
#
#-------------------------------------------------

QT    += core gui opengl testlib network script webkit
TARGET = CreatureViewer
TEMPLATE = app
CONFIG += silent

# genecraft core
INCLUDEPATH += \
    ../genecraft/core \
    ../genecraft/core/engines \
    ../genecraft/core/entities \
    ../genecraft/core/experiment \
    ../genecraft/core/factories \
    ../genecraft/core/ui \
    ../genecraft/core/world \
    ../genecraft/core/utils

# genecraft apps
INCLUDEPATH += \
    ../genecraft/apps/genecraft \
    ../genecraft/apps/genecraft/creatureviewer \
    ../genecraft/apps/genecraft/creatureviewer/inputlisteners \


#library related
INCLUDEPATH  += \
    ../lib/bullet/src \
    ../lib/qxt/src/core \
    ../lib/qwt/include/

INCLUDEPATH += ../lib/ogre/include/OGRE \
               ../lib/ogre/include \
               ../lib/ogre/boost_1_44 # for win32
               #../lib/ogre/boost_1_46_1/ # for macos

#suppress warning for thoses systems
QMAKE_CXXFLAGS  += -isystem../lib/ogre/boost_1_46_1/  # boost_1_44 for win32
QMAKE_CXXFLAGS  += -isystem../lib/ogre/include
QMAKE_CXXFLAGS  += -isystem../lib/ogre/include/OGRE

#suppress warning for thoses systems
QMAKE_CXXFLAGS  += -isystem../lib/bullet/src
QMAKE_CXXFLAGS  += -isystem../lib/qxt/src/core
QMAKE_CXXFLAGS  += -isystem../lib/qwt/include

    LIBS += -L../lib/bullet/lib
    LIBS += -L../lib/qxt/lib
    LIBS += -L../lib/qwt/lib
win32 {
    LIBS += -L../lib/ogre/bin/Release
    LIBS += -lOgreMain
}

unix {
    LIBS += -L../lib/ogre/lib
    LIBS += -F../lib/ogre/lib/release/
    LIBS += -framework Ogre
}

LIBS += -lBulletDynamics
LIBS += -lBulletCollision
LIBS += -lLinearMath
LIBS += -lQxtCore
LIBS += -lqwt
LIBS += -lOgreTerrain
#LIBS += -lOgreMain
#LIBS += -lConvexDecomposition
#LIBS += -lBulletWorldImporter -lBulletFileLoader
#LIBS += -lBulletMultiThreaded
#LIBS += -lBulletSoftBody
#LIBS += -lGIMPACTUtils
#LIBS += -lgle
#LIBS += -lglsmap
#LIBS += -lglut32
#LIBS += -lGLUI
#LIBS += -lMiniCL
#LIBS += -lmui
#LIBS += -lOpenGLSupport

SOURCES += \
    ../genecraft/core/engines/engine.cpp \
    ../genecraft/core/engines/simulationmanager.cpp \
    ../genecraft/core/engines/events/inspectorsinputmanager.cpp \
    ../genecraft/core/engines/events/inputlistener.cpp \
    ../genecraft/core/engines/events/eventsmanager.cpp \
    ../genecraft/core/engines/bullet/bulletengine.cpp \
    ../genecraft/core/engines/bullet/rigidbodyorigin.cpp \
    ../genecraft/core/engines/bullet/shapes/btshape.cpp \
    ../genecraft/core/engines/bullet/shapes/btbox.cpp \
    ../genecraft/core/engines/bullet/shapes/btsphere.cpp \
    ../genecraft/core/engines/bullet/shapes/btcylinder.cpp \
    ../genecraft/core/engines/bullet/shapes/btbone.cpp \
    ../genecraft/core/engines/bulletogre/shapes/btobox.cpp \
    ../genecraft/core/engines/bulletogre/shapes/btosphere.cpp \
    ../genecraft/core/engines/bulletogre/bulletogreengine.cpp \
    ../genecraft/core/engines/bulletogre/shapes/btocylinder.cpp \
    ../genecraft/core/engines/bulletogre/shapes/btobone.cpp \
    ../genecraft/core/engines/ogre/ogrewidget.cpp \
    ../genecraft/core/engines/ogre/ogreengine.cpp \
    ../genecraft/core/engines/ogre/entities/ogrefreecamera.cpp \
    ../genecraft/core/engines/entities/entitiesengine.cpp \
    ../genecraft/core/entities/entity.cpp \
    ../genecraft/core/entities/body/treeshape.cpp \
    ../genecraft/core/entities/body/fixation.cpp \
    ../genecraft/core/entities/body/bone.cpp \
    ../genecraft/core/entities/brain/synapse.cpp \
    ../genecraft/core/entities/brain/sinusin.cpp \
    ../genecraft/core/entities/brain/brainpluggrid.cpp \
    ../genecraft/core/entities/brain/brainnode.cpp \
    ../genecraft/core/entities/brain/brain.cpp \
    ../genecraft/core/entities/brain/brainfunctional.cpp \
    ../genecraft/core/entities/brain/brainin.cpp \
    ../genecraft/core/entities/brain/brainout.cpp \
    ../genecraft/core/entities/sensors/sensor.cpp \
    ../genecraft/core/entities/sensors/positionsensor.cpp \
    ../genecraft/core/entities/sensors/gyroscopicsensor.cpp \
    ../genecraft/core/entities/sensors/accelerometersensor.cpp \
    ../genecraft/core/entities/sensors/smellsensor.cpp \
    ../genecraft/core/entities/sensors/boxsmellsensor.cpp \
    ../genecraft/core/entities/sensors/distancesensor.cpp \
    ../genecraft/core/entities/sensors/contactsensor.cpp \
    ../genecraft/core/entities/effectors/effector.cpp \
    ../genecraft/core/entities/effectors/rotationalmotorseffector.cpp \
    ../genecraft/core/entities/effectors/grippereffector.cpp \
    ../genecraft/core/entities/effectors/flyingeffector.cpp \
    ../genecraft/core/entities/entityfamily.cpp \
    ../genecraft/core/entities/families/genericfamily.cpp \
    ../genecraft/core/entities/families/spiderfamily.cpp \
    ../genecraft/core/entities/families/antfamily.cpp \
    ../genecraft/core/entities/families/caterpillarfamily.cpp \
    ../genecraft/core/entities/families/snakefamily.cpp \
    ../genecraft/core/entities/mutation/mutationsmanager.cpp \
    ../genecraft/core/entities/mutation/mutation.cpp \
    ../genecraft/core/entities/mutation/floatmutation.cpp \
    ../genecraft/core/entities/mutation/brainnodemutation.cpp \
    ../genecraft/core/entities/mutation/integermutation.cpp \
    ../genecraft/core/entities/mutation/bonelimitsmutation.cpp \
    ../genecraft/core/entities/mutation/simpleprobabilitymutation.cpp \
    ../genecraft/core/entities/mutation/structuralmutation.cpp \
    ../genecraft/core/entities/mutation/structurallist.cpp \
    ../genecraft/core/entities/mutation/crossovermanager.cpp \
    ../genecraft/core/entities/statistics/statisticsstorage.cpp \
    ../genecraft/core/entities/statistics/treeshapestats.cpp \
    ../genecraft/core/entities/statistics/statisticsprovider.cpp \
    ../genecraft/core/entities/statistics/fixationstats.cpp \
    ../genecraft/core/world/btworld.cpp \
    ../genecraft/core/world/btscene.cpp \
    ../genecraft/core/world/btbiome.cpp \
    ../genecraft/core/world/btoworld.cpp \
    ../genecraft/core/world/btoscene.cpp \
    ../genecraft/core/world/btobiome.cpp \
    ../genecraft/core/world/spawn.cpp \
    ../genecraft/core/factories/ressources/jsonfile.cpp \
    ../genecraft/core/factories/ressources/dbrecord.cpp \
    ../genecraft/core/factories/ressources/ressourcesmanager.cpp \
    ../genecraft/core/factories/ressources/ressource.cpp \
    ../genecraft/core/factories/btofactory.cpp \
    ../genecraft/core/factories/btfactory.cpp \
    ../genecraft/core/factories/creaturefactory.cpp \
    ../genecraft/core/factories/btworldfactory.cpp \
    ../genecraft/core/factories/btoworldfactory.cpp \
    ../genecraft/core/factories/btshapesfactory.cpp \
    ../genecraft/core/factories/btoshapesfactory.cpp \
    ../genecraft/core/experiment/result.cpp \
    ../genecraft/core/experiment/experimentmanager.cpp \
    ../genecraft/core/experiment/experiment.cpp \
    ../genecraft/core/experiment/resultsmanager.cpp \
    ../genecraft/core/ui/widgets/entities/brainpropertiescontroller.cpp \
    ../genecraft/core/ui/widgets/entities/statisticspropertiescontroller.cpp \
    ../genecraft/core/ui/widgets/entities/fixationpropertiescontroller.cpp \
    ../genecraft/core/ui/widgets/experiments/experimentspropertiescontroller.cpp \
    ../genecraft/core/ui/widgets/experiments/floatmutationcontroller.cpp \
    ../genecraft/core/ui/widgets/experiments/integermutationcontroller.cpp \
    ../genecraft/core/ui/widgets/experiments/simpleprobabilitycontroller.cpp \
    ../genecraft/core/ui/widgets/experiments/structuralmutationcontroller.cpp \
    ../genecraft/core/ui/widgets/experiments/mutationelementcontroller.cpp \
    ../genecraft/core/ui/widgets/experiments/workerctrl.cpp \
    ../genecraft/core/ui/widgets/experiments/ressourcesbrowser.cpp \
    ../genecraft/core/ui/widgets/experiments/experimentctrl.cpp \
    ../genecraft/core/ui/widgets/ogrebulletwindows.cpp \
    ../genecraft/core/ui/widgets/entities/generic6dofconstraintcontroller.cpp \
    ../genecraft/core/ui/widgets/entities/bonepropertiescontroller.cpp \
    ../genecraft/core/ui/widgets/entities/pluggridvisualizer.cpp \
    ../genecraft/core/ui/widgets/entities/entitypropertiescontroller.cpp \
    ../genecraft/core/ui/widgets/entities/pluggriddesignvisualizer.cpp \
    ../genecraft/core/utils/tools.cpp \
    ../genecraft/apps/genecraft/creatureviewer/ui/creatureviewerwindow.cpp \
    ../genecraft/apps/genecraft/creatureviewer/ui/creatureviewerabout.cpp \
    ../genecraft/apps/genecraft/creatureviewer/inputlisteners/creatureviewerinputmanager.cpp \
    main.cpp \
    ../genecraft/apps/genecraft/creatureviewer/ui/welcomewidget.cpp \
    ../genecraft/core/ui/widgets/experiments/conversionctrl.cpp \
    ../genecraft/core/ui/widgets/plot/fitnessplot.cpp \
    ../genecraft/core/ui/widgets/experiments/floordialog.cpp \
    ../genecraft/core/engines/terrain/terrain.cpp \
    ../genecraft/core/entities/effectors/brainoutmotor.cpp \
    ../genecraft/core/factories/genome/genomemodifier.cpp \
    ../genecraft/core/factories/genome/genomebuilder.cpp \
    ../genecraft/core/ui/widgets/graphicalwidget.cpp \
    ../genecraft/core/entities/body/symmetry.cpp \
    ../genecraft/core/entities/body/recursion.cpp


HEADERS += \
    ../genecraft/core/engines/engine.h \
    ../genecraft/core/engines/simulationmanager.h \
    ../genecraft/core/engines/events/eventsmanager.h \
    ../genecraft/core/engines/events/inspectorsinputmanager.h \
    ../genecraft/core/engines/events/inputlistener.h \
    ../genecraft/core/engines/bullet/bulletengine.h \
    ../genecraft/core/engines/bullet/rigidbodyorigin.h \
    ../genecraft/core/engines/bullet/shapes/btshape.h \
    ../genecraft/core/engines/bullet/shapes/btbox.h \
    ../genecraft/core/engines/bullet/shapes/btsphere.h \
    ../genecraft/core/engines/bullet/shapes/btcylinder.h \
    ../genecraft/core/engines/bullet/shapes/btbone.h \
    ../genecraft/core/engines/bulletogre/shapes/btobox.h \
    ../genecraft/core/engines/bulletogre/shapes/btosphere.h \
    ../genecraft/core/engines/bulletogre/bulletogreengine.h \
    ../genecraft/core/engines/bulletogre/shapes/btocylinder.h \
    ../genecraft/core/engines/bulletogre/shapes/btobone.h \
    ../genecraft/core/engines/entities/entitiesengine.h \
    ../genecraft/core/engines/ogre/ogreengine.h \
    ../genecraft/core/engines/ogre/entities/ogrefreecamera.h \
    ../genecraft/core/engines/ogre/ogrewidget.h \
    ../genecraft/core/entities/entity.h \
    ../genecraft/core/entities/body/treeshape.h \
    ../genecraft/core/entities/body/bone.h \
    ../genecraft/core/entities/body/fixation.h \
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
    ../genecraft/core/entities/sensors/smellsensor.h \
    ../genecraft/core/entities/sensors/boxsmellsensor.h \
    ../genecraft/core/entities/sensors/distancesensor.h \
    ../genecraft/core/entities/effectors/effector.h \
    ../genecraft/core/entities/effectors/rotationalmotorseffector.h \
    ../genecraft/core/entities/effectors/grippereffector.h \
    ../genecraft/core/entities/effectors/flyingeffector.h \
    ../genecraft/core/entities/entityfamily.h \
    ../genecraft/core/entities/families/snakefamily.h \
    ../genecraft/core/entities/families/spiderfamily.h \
    ../genecraft/core/entities/families/antfamily.h \
    ../genecraft/core/entities/families/caterpillarfamily.h \
    ../genecraft/core/entities/families/genericfamily.h \
    ../genecraft/core/entities/statistics/statisticsstorage.h \
    ../genecraft/core/entities/statistics/treeshapestats.h \
    ../genecraft/core/entities/statistics/statisticsprovider.h \
    ../genecraft/core/entities/statistics/fixationstats.h \
    ../genecraft/core/entities/mutation/mutationsmanager.h \
    ../genecraft/core/entities/mutation/mutation.h \
    ../genecraft/core/entities/mutation/floatmutation.h \
    ../genecraft/core/entities/mutation/brainnodemutation.h \
    ../genecraft/core/entities/mutation/integermutation.h \
    ../genecraft/core/entities/mutation/simpleprobabilitymutation.h \
    ../genecraft/core/entities/mutation/structuralmutation.h \
    ../genecraft/core/entities/mutation/structurallist.h \
    ../genecraft/core/entities/mutation/crossovermanager.h \
    ../genecraft/core/entities/mutation/bonelimitsmutation.h \
    ../genecraft/core/factories/ressources/ressource.h \
    ../genecraft/core/factories/btshapesfactory.h \
    ../genecraft/core/factories/btoshapesfactory.h \
    ../genecraft/core/factories/ressources/jsonfile.h \
    ../genecraft/core/factories/ressources/dbrecord.h \
    ../genecraft/core/factories/btofactory.h \
    ../genecraft/core/factories/btfactory.h \
    ../genecraft/core/factories/creaturefactory.h \
    ../genecraft/core/factories/btworldfactory.h \
    ../genecraft/core/factories/btoworldfactory.h \
    ../genecraft/core/factories/ressources/ressourcesmanager.h \
    ../genecraft/core/world/btworld.h \
    ../genecraft/core/world/btscene.h \
    ../genecraft/core/world/btbiome.h \
    ../genecraft/core/world/btoworld.h \
    ../genecraft/core/world/btoscene.h \
    ../genecraft/core/world/btobiome.h \
    ../genecraft/core/world/spawn.h \
    ../genecraft/core/experiment/result.h \
    ../genecraft/core/experiment/experimentmanager.h \
    ../genecraft/core/experiment/experiment.h \
    ../genecraft/core/experiment/resultsmanager.h \
    ../genecraft/core/ui/widgets/experiments/structuralmutationcontroller.h \
    ../genecraft/core/ui/widgets/experiments/mutationelementcontroller.h \
    ../genecraft/core/ui/widgets/experiments/workerctrl.h \
    ../genecraft/core/ui/widgets/experiments/ressourcesbrowser.h \
    ../genecraft/core/ui/widgets/experiments/ressourcesItems.h \
    ../genecraft/core/ui/widgets/experiments/experimentctrl.h \
    ../genecraft/core/ui/widgets/experiments/experimentspropertiescontroller.h \
    ../genecraft/core/ui/widgets/experiments/floatmutationcontroller.h \
    ../genecraft/core/ui/widgets/experiments/integermutationcontroller.h \
    ../genecraft/core/ui/widgets/experiments/simpleprobabilitycontroller.h \
    ../genecraft/core/ui/widgets/entities/brainpropertiescontroller.h \
    ../genecraft/core/ui/widgets/entities/statisticspropertiescontroller.h \
    ../genecraft/core/ui/widgets/entities/fixationpropertiescontroller.h \
    ../genecraft/core/ui/widgets/entities/pluggriddesignvisualizer.h \
    ../genecraft/core/ui/widgets/entities/bodyitems.h \
    ../genecraft/core/ui/widgets/entities/entitypropertiescontroller.h \
    ../genecraft/core/ui/widgets/entities/pluggridvisualizer.h \
    ../genecraft/core/ui/widgets/entities/bonepropertiescontroller.h \
    ../genecraft/core/ui/widgets/entities/generic6dofconstraintcontroller.h \
    ../genecraft/core/ui/widgets/ogrebulletwindows.h \
    ../genecraft/core/utils/tools.h \
    ../genecraft/apps/genecraft/creatureviewer/ui/creatureviewerwindow.h \
    ../genecraft/apps/genecraft/creatureviewer/ui/creatureviewerabout.h \
    ../genecraft/apps/genecraft/creatureviewer/inputlisteners/creatureviewerinputmanager.h \
    ../genecraft/apps/genecraft/creatureviewer/ui/welcomewidget.h \
    ../genecraft/core/genecraftcoreclasses.h \
    ../genecraft/core/ui/widgets/experiments/conversionctrl.h \
    ../genecraft/core/ui/widgets/plot/fitnessplot.h \
    ../genecraft/core/ui/widgets/experiments/floordialog.h \
    ../genecraft/core/engines/terrain/terrain.h \
    ../genecraft/core/entities/effectors/brainoutmotor.h \
    ../genecraft/core/factories/genome/genomemodifier.h \
    ../genecraft/core/factories/genome/genomebuilder.h \
    ../genecraft/core/ui/widgets/graphicalwidget.h \
    ../genecraft/core/entities/body/symmetry.h \
    ../genecraft/core/entities/body/recursion.h

FORMS += \
    ../genecraft/core/ui/widgets/ogrebulletwindows.ui \
    ../genecraft/core/ui/widgets/entities/generic6dofconstraintcontroller.ui \
    ../genecraft/core/ui/widgets/entities/bonepropertiescontroller.ui \
    ../genecraft/core/ui/widgets/entities/entitypropertiescontroller.ui \
    ../genecraft/core/ui/widgets/entities/brainpropertiescontroller.ui \
    ../genecraft/core/ui/widgets/entities/statisticspropertiescontroller.ui \
    ../genecraft/core/ui/widgets/entities/fixationpropertiescontroller.ui \
    ../genecraft/core/ui/widgets/experiments/experimentspropertiescontroller.ui \
    ../genecraft/core/ui/widgets/experiments/floatmutationcontroller.ui \
    ../genecraft/core/ui/widgets/experiments/integermutationcontroller.ui \
    ../genecraft/core/ui/widgets/experiments/simpleprobabilitycontroller.ui \
    ../genecraft/core/ui/widgets/experiments/structuralmutationcontroller.ui \
    ../genecraft/core/ui/widgets/experiments/mutationelementcontroller.ui \
    ../genecraft/core/ui/widgets/experiments/workerctrl.ui \
    ../genecraft/core/ui/widgets/experiments/ressourcesbrowser.ui \
    ../genecraft/core/ui/widgets/experiments/experimentctrl.ui \
    ../genecraft/apps/genecraft/creatureviewer/ui/creatureviewerwindow.ui \
    ../genecraft/apps/genecraft/creatureviewer/ui/creatureviewerabout.ui \
    ../genecraft/apps/genecraft/creatureviewer/ui/welcomewidget.ui \
    ../genecraft/core/ui/widgets/experiments/conversionctrl.ui \
    ../genecraft/core/ui/widgets/experiments/floordialog.ui

RESOURCES += \
    ../genecraft/core/ressources/ressources.qrc








