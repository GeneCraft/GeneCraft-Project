#-------------------------------------------------
#
# Project created by QtCreator 2011-05-16T17:50:27
#
#-------------------------------------------------

QT       += core gui opengl testlib network script webkit
TARGET = CreatureViewer
TEMPLATE = app

# genelab core
INCLUDEPATH += \
    ../genelab/core \
    ../genelab/core/engines \
    ../genelab/core/entities \
    ../genelab/core/experiment \
    ../genelab/core/factories \
    ../genelab/core/ui \
    ../genelab/core/world \
    ../genelab/core/utils

# genelab apps
INCLUDEPATH += \
    ../genelab/apps/genelab \
    ../genelab/apps/genelab/creatureviewer \
    ../genelab/apps/genelab/creatureviewer/inputlisteners \


#library related
INCLUDEPATH  += \
    ../lib/bullet/src \
    ../lib/bullet/Extra/ConvexDecomposition \
    ../lib/qxt/src/core

 win32 {
    INCLUDEPATH += ../lib/ogre/include/OGRE \
                   ../lib/ogre/include/OIS \
                   ../lib/ogre/include \
                   ../lib/ogre/boost_1_44

    QMAKE_CXXFLAGS  += -isystem../lib/ogre/boost_1_44
    QMAKE_CXXFLAGS  += -isystem../lib/ogre/include
    QMAKE_CXXFLAGS  += -isystem../lib/ogre/include/OGRE
    QMAKE_CXXFLAGS  += -isystem../lib/ogre/include/OIS
 }
 unix {
    INCLUDEPATH += ../lib/ogre/Dependencies/include
#todo bether
    INCLUDEPATH += /Users/cyprienhuissoud/Downloads/ogre_src_v1-7-3/build/lib/RelWithDebInfo/Ogre.framework/Headers
    QMAKE_CXXFLAGS  += -isystem/Users/cyprienhuissoud/Downloads/ogre_src_v1-7-3/build/lib/RelWithDebInfo/Ogre.framework/Headers
 }

QMAKE_CXXFLAGS  += -isystem../lib/bullet/src
QMAKE_CXXFLAGS  += -isystem../lib/bullet/Extra/ConvexDecomposition
QMAKE_CXXFLAGS  += -isystem../lib/qxt/src/core
QMAKE_CXXFLAGS  += -isystem../lib/qwt/src

win32 {
    LIBS += -L../lib/bullet/lib
    LIBS += -L../lib/qxt/lib
    LIBS += -L../lib/ogre/bin/Release
    LIBS += -lOgreMain -lOIS
}

unix {
    LIBS += -L/Users/cyprienhuissoud/Downloads/Dependencies/bin/Release
    LIBS += -L../lib/qxt/lib
    LIBS += -L../lib/bullet/lib
    LIBS += -F/Users/cyprienhuissoud/Downloads/ogre_src_v1-7-3/build/lib/RelWithDebInfo
    LIBS += -framework Ogre
    LIBS += -lzzip
    LIBS += -lfreetype
    LIBS += -lfreeimage
    LIBS += -lOIS
}

LIBS += -lBulletDynamics
LIBS += -lBulletCollision
LIBS += -lLinearMath
LIBS += -lQxtCore
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
    ../genelab/core/engines/engine.cpp \
    ../genelab/core/engines/simulationmanager.cpp \
    ../genelab/core/engines/events/inspectorsinputmanager.cpp \
    ../genelab/core/engines/events/inputlistener.cpp \
    ../genelab/core/engines/events/eventsmanager.cpp \
    ../genelab/core/engines/bullet/bulletengine.cpp \
    ../genelab/core/engines/bullet/rigidbodyorigin.cpp \
    ../genelab/core/engines/bullet/shapes/btshape.cpp \
    ../genelab/core/engines/bullet/shapes/btbox.cpp \
    ../genelab/core/engines/bullet/shapes/btsphere.cpp \
    ../genelab/core/engines/bullet/shapes/btcylinder.cpp \
    ../genelab/core/engines/bullet/shapes/btbone.cpp \
    ../genelab/core/engines/bulletogre/shapes/btobox.cpp \
    ../genelab/core/engines/bulletogre/shapes/btosphere.cpp \
    ../genelab/core/engines/bulletogre/bulletogreengine.cpp \
    ../genelab/core/engines/bulletogre/shapes/btocylinder.cpp \
    ../genelab/core/engines/bulletogre/shapes/btobone.cpp \
    ../genelab/core/engines/ogre/ogrewidget.cpp \
    ../genelab/core/engines/ogre/ogreengine.cpp \
    ../genelab/core/engines/ogre/entities/ogrefreecamera.cpp \
    ../genelab/core/engines/entities/entitiesengine.cpp \
    ../genelab/core/entities/entity.cpp \
    ../genelab/core/entities/body/treeshape.cpp \
    ../genelab/core/entities/body/fixation.cpp \
    ../genelab/core/entities/body/bone.cpp \
    ../genelab/core/entities/brain/synapse.cpp \
    ../genelab/core/entities/brain/sinusin.cpp \
    ../genelab/core/entities/brain/brainpluggrid.cpp \
    ../genelab/core/entities/brain/brainnode.cpp \
    ../genelab/core/entities/brain/brain.cpp \
    ../genelab/core/entities/brain/brainfunctional.cpp \
    ../genelab/core/entities/brain/brainin.cpp \
    ../genelab/core/entities/brain/brainout.cpp \
    ../genelab/core/entities/sensors/sensor.cpp \
    ../genelab/core/entities/sensors/positionsensor.cpp \
    ../genelab/core/entities/sensors/gyroscopicsensor.cpp \
    ../genelab/core/entities/sensors/accelerometersensor.cpp \
    ../genelab/core/entities/sensors/smellsensor.cpp \
    ../genelab/core/entities/sensors/boxsmellsensor.cpp \
    ../genelab/core/entities/sensors/distancesensor.cpp \
    ../genelab/core/entities/sensors/contactsensor.cpp \
    ../genelab/core/entities/effectors/effector.cpp \
    ../genelab/core/entities/effectors/rotationalmotorseffector.cpp \
    ../genelab/core/entities/effectors/grippereffector.cpp \
    ../genelab/core/entities/effectors/flyingeffector.cpp \
    ../genelab/core/entities/entityfamily.cpp \
    ../genelab/core/entities/families/genericfamily.cpp \
    ../genelab/core/entities/families/spiderfamily.cpp \
    ../genelab/core/entities/families/antfamily.cpp \
    ../genelab/core/entities/families/caterpillarfamily.cpp \
    ../genelab/core/entities/families/snakefamily.cpp \
    ../genelab/core/entities/mutation/mutationsmanager.cpp \
    ../genelab/core/entities/mutation/mutation.cpp \
    ../genelab/core/entities/mutation/floatmutation.cpp \
    ../genelab/core/entities/mutation/brainnodemutation.cpp \
    ../genelab/core/entities/mutation/integermutation.cpp \
    ../genelab/core/entities/mutation/bonelimitsmutation.cpp \
    ../genelab/core/entities/mutation/simpleprobabilitymutation.cpp \
    ../genelab/core/entities/mutation/structuralmutation.cpp \
    ../genelab/core/entities/mutation/structurallist.cpp \
    ../genelab/core/entities/mutation/crossovermanager.cpp \
    ../genelab/core/entities/statistics/statisticsstorage.cpp \
    ../genelab/core/entities/statistics/treeshapestats.cpp \
    ../genelab/core/entities/statistics/statisticsprovider.cpp \
    ../genelab/core/entities/statistics/fixationstats.cpp \
    ../genelab/core/world/btworld.cpp \
    ../genelab/core/world/btscene.cpp \
    ../genelab/core/world/btbiome.cpp \
    ../genelab/core/world/btoworld.cpp \
    ../genelab/core/world/btoscene.cpp \
    ../genelab/core/world/btobiome.cpp \
    ../genelab/core/world/spawn.cpp \
    ../genelab/core/factories/ressources/jsonfile.cpp \
    ../genelab/core/factories/ressources/dbrecord.cpp \
    ../genelab/core/factories/ressources/ressourcesmanager.cpp \
    ../genelab/core/factories/ressources/ressource.cpp \
    ../genelab/core/factories/btofactory.cpp \
    ../genelab/core/factories/btfactory.cpp \
    ../genelab/core/factories/creaturefactory.cpp \
    ../genelab/core/factories/btworldfactory.cpp \
    ../genelab/core/factories/btoworldfactory.cpp \
    ../genelab/core/factories/btshapesfactory.cpp \
    ../genelab/core/factories/btoshapesfactory.cpp \
    ../genelab/core/experiment/result.cpp \
    ../genelab/core/experiment/experimentmanager.cpp \
    ../genelab/core/experiment/experiment.cpp \
    ../genelab/core/experiment/resultsmanager.cpp \
    ../genelab/core/ui/widgets/entities/brainpropertiescontroller.cpp \
    ../genelab/core/ui/widgets/entities/statisticspropertiescontroller.cpp \
    ../genelab/core/ui/widgets/entities/fixationpropertiescontroller.cpp \
    ../genelab/core/ui/widgets/experiments/experimentspropertiescontroller.cpp \
    ../genelab/core/ui/widgets/experiments/floatmutationcontroller.cpp \
    ../genelab/core/ui/widgets/experiments/integermutationcontroller.cpp \
    ../genelab/core/ui/widgets/experiments/simpleprobabilitycontroller.cpp \
    ../genelab/core/ui/widgets/experiments/structuralmutationcontroller.cpp \
    ../genelab/core/ui/widgets/experiments/mutationelementcontroller.cpp \
    ../genelab/core/ui/widgets/experiments/workerctrl.cpp \
    ../genelab/core/ui/widgets/experiments/ressourcesbrowser.cpp \
    ../genelab/core/ui/widgets/experiments/experimentctrl.cpp \
    ../genelab/core/ui/widgets/ogrebulletwindows.cpp \
    ../genelab/core/ui/widgets/entities/generic6dofconstraintcontroller.cpp \
    ../genelab/core/ui/widgets/entities/bonepropertiescontroller.cpp \
    ../genelab/core/ui/widgets/entities/pluggridvisualizer.cpp \
    ../genelab/core/ui/widgets/entities/entitypropertiescontroller.cpp \
    ../genelab/core/ui/widgets/entities/pluggriddesignvisualizer.cpp \
    ../genelab/core/utils/tools.cpp \
    ../genelab/apps/genelab/creatureviewer/ui/creatureviewerwindow.cpp \
    ../genelab/apps/genelab/creatureviewer/ui/creatureviewerabout.cpp \
    ../genelab/apps/genelab/creatureviewer/inputlisteners/creatureviewerinputmanager.cpp \
    main.cpp \
    ../genelab/apps/genelab/creatureviewer/ui/welcomewidget.cpp


HEADERS += \
    ../genelab/core/engines/engine.h \
    ../genelab/core/engines/simulationmanager.h \
    ../genelab/core/engines/events/eventsmanager.h \
    ../genelab/core/engines/events/inspectorsinputmanager.h \
    ../genelab/core/engines/events/inputlistener.h \
    ../genelab/core/engines/bullet/bulletengine.h \
    ../genelab/core/engines/bullet/rigidbodyorigin.h \
    ../genelab/core/engines/bullet/shapes/btshape.h \
    ../genelab/core/engines/bullet/shapes/btbox.h \
    ../genelab/core/engines/bullet/shapes/btsphere.h \
    ../genelab/core/engines/bullet/shapes/btcylinder.h \
    ../genelab/core/engines/bullet/shapes/btbone.h \
    ../genelab/core/engines/bulletogre/shapes/btobox.h \
    ../genelab/core/engines/bulletogre/shapes/btosphere.h \
    ../genelab/core/engines/bulletogre/bulletogreengine.h \
    ../genelab/core/engines/bulletogre/shapes/btocylinder.h \
    ../genelab/core/engines/bulletogre/shapes/btobone.h \
    ../genelab/core/engines/entities/entitiesengine.h \
    ../genelab/core/engines/ogre/ogreengine.h \
    ../genelab/core/engines/ogre/entities/ogrefreecamera.h \
    ../genelab/core/engines/ogre/ogrewidget.h \
    ../genelab/core/entities/entity.h \
    ../genelab/core/entities/body/treeshape.h \
    ../genelab/core/entities/body/bone.h \
    ../genelab/core/entities/body/fixation.h \
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
    ../genelab/core/entities/sensors/smellsensor.h \
    ../genelab/core/entities/sensors/boxsmellsensor.h \
    ../genelab/core/entities/sensors/distancesensor.h \
    ../genelab/core/entities/effectors/effector.h \
    ../genelab/core/entities/effectors/rotationalmotorseffector.h \
    ../genelab/core/entities/effectors/grippereffector.h \
    ../genelab/core/entities/effectors/flyingeffector.h \
    ../genelab/core/entities/entityfamily.h \
    ../genelab/core/entities/families/snakefamily.h \
    ../genelab/core/entities/families/spiderfamily.h \
    ../genelab/core/entities/families/antfamily.h \
    ../genelab/core/entities/families/caterpillarfamily.h \
    ../genelab/core/entities/families/genericfamily.h \
    ../genelab/core/entities/statistics/statisticsstorage.h \
    ../genelab/core/entities/statistics/treeshapestats.h \
    ../genelab/core/entities/statistics/statisticsprovider.h \
    ../genelab/core/entities/statistics/fixationstats.h \
    ../genelab/core/entities/mutation/mutationsmanager.h \
    ../genelab/core/entities/mutation/mutation.h \
    ../genelab/core/entities/mutation/floatmutation.h \
    ../genelab/core/entities/mutation/brainnodemutation.h \
    ../genelab/core/entities/mutation/integermutation.h \
    ../genelab/core/entities/mutation/simpleprobabilitymutation.h \
    ../genelab/core/entities/mutation/structuralmutation.h \
    ../genelab/core/entities/mutation/structurallist.h \
    ../genelab/core/entities/mutation/crossovermanager.h \
    ../genelab/core/entities/mutation/bonelimitsmutation.h \
    ../genelab/core/factories/ressources/ressource.h \
    ../genelab/core/factories/btshapesfactory.h \
    ../genelab/core/factories/btoshapesfactory.h \
    ../genelab/core/factories/ressources/jsonfile.h \
    ../genelab/core/factories/ressources/dbrecord.h \
    ../genelab/core/factories/btofactory.h \
    ../genelab/core/factories/btfactory.h \
    ../genelab/core/factories/creaturefactory.h \
    ../genelab/core/factories/btworldfactory.h \
    ../genelab/core/factories/btoworldfactory.h \
    ../genelab/core/factories/ressources/ressourcesmanager.h \
    ../genelab/core/world/btworld.h \
    ../genelab/core/world/btscene.h \
    ../genelab/core/world/btbiome.h \
    ../genelab/core/world/btoworld.h \
    ../genelab/core/world/btoscene.h \
    ../genelab/core/world/btobiome.h \
    ../genelab/core/world/spawn.h \
    ../genelab/core/experiment/result.h \
    ../genelab/core/experiment/experimentmanager.h \
    ../genelab/core/experiment/experiment.h \
    ../genelab/core/experiment/resultsmanager.h \
    ../genelab/core/ui/widgets/experiments/structuralmutationcontroller.h \
    ../genelab/core/ui/widgets/experiments/mutationelementcontroller.h \
    ../genelab/core/ui/widgets/experiments/workerctrl.h \
    ../genelab/core/ui/widgets/experiments/ressourcesbrowser.h \
    ../genelab/core/ui/widgets/experiments/ressourcesItems.h \
    ../genelab/core/ui/widgets/experiments/experimentctrl.h \
    ../genelab/core/ui/widgets/experiments/experimentspropertiescontroller.h \
    ../genelab/core/ui/widgets/experiments/floatmutationcontroller.h \
    ../genelab/core/ui/widgets/experiments/integermutationcontroller.h \
    ../genelab/core/ui/widgets/experiments/simpleprobabilitycontroller.h \
    ../genelab/core/ui/widgets/entities/brainpropertiescontroller.h \
    ../genelab/core/ui/widgets/entities/statisticspropertiescontroller.h \
    ../genelab/core/ui/widgets/entities/fixationpropertiescontroller.h \
    ../genelab/core/ui/widgets/entities/pluggriddesignvisualizer.h \
    ../genelab/core/ui/widgets/entities/bodyitems.h \
    ../genelab/core/ui/widgets/entities/entitypropertiescontroller.h \
    ../genelab/core/ui/widgets/entities/pluggridvisualizer.h \
    ../genelab/core/ui/widgets/entities/bonepropertiescontroller.h \
    ../genelab/core/ui/widgets/entities/generic6dofconstraintcontroller.h \
    ../genelab/core/ui/widgets/ogrebulletwindows.h \
    ../genelab/core/utils/tools.h \
    ../genelab/apps/genelab/creatureviewer/ui/creatureviewerwindow.h \
    ../genelab/apps/genelab/creatureviewer/ui/creatureviewerabout.h \
    ../genelab/apps/genelab/creatureviewer/inputlisteners/creatureviewerinputmanager.h \
    ../genelab/apps/genelab/creatureviewer/ui/welcomewidget.h \
    ../genelab/core/genecraftcoreclasses.h

FORMS += \
    ../genelab/core/ui/widgets/ogrebulletwindows.ui \
    ../genelab/core/ui/widgets/entities/generic6dofconstraintcontroller.ui \
    ../genelab/core/ui/widgets/entities/bonepropertiescontroller.ui \
    ../genelab/core/ui/widgets/entities/entitypropertiescontroller.ui \
    ../genelab/core/ui/widgets/entities/brainpropertiescontroller.ui \
    ../genelab/core/ui/widgets/entities/statisticspropertiescontroller.ui \
    ../genelab/core/ui/widgets/entities/fixationpropertiescontroller.ui \
    ../genelab/core/ui/widgets/experiments/experimentspropertiescontroller.ui \
    ../genelab/core/ui/widgets/experiments/floatmutationcontroller.ui \
    ../genelab/core/ui/widgets/experiments/integermutationcontroller.ui \
    ../genelab/core/ui/widgets/experiments/simpleprobabilitycontroller.ui \
    ../genelab/core/ui/widgets/experiments/structuralmutationcontroller.ui \
    ../genelab/core/ui/widgets/experiments/mutationelementcontroller.ui \
    ../genelab/core/ui/widgets/experiments/workerctrl.ui \
    ../genelab/core/ui/widgets/experiments/ressourcesbrowser.ui \
    ../genelab/core/ui/widgets/experiments/experimentctrl.ui \
    ../genelab/apps/genelab/creatureviewer/ui/creatureviewerwindow.ui \
    ../genelab/apps/genelab/creatureviewer/ui/creatureviewerabout.ui \
    ../genelab/apps/genelab/creatureviewer/ui/welcomewidget.ui

RESOURCES += \
    ../genelab/core/ressources/ressources.qrc

TRANSLATIONS = genelab_global_fr.ts
