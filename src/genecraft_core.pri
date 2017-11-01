#Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud
#
#This file is part of Genecraft-Project.
#
#Genecraft-Project is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#Genecraft-Project is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.

# genecraft core
INCLUDEPATH += \
    genecraft/core \
    genecraft/core/engines \
    genecraft/core/entities \
    genecraft/core/experiment \
    genecraft/core/factories/base \
    genecraft/core/factories \
    genecraft/core/world/base \
    genecraft/core/world \
    genecraft/core/utils


#library related
INCLUDEPATH  += \
    ../lib/bullet/src \
    ../lib/qwt/src


#suppress warning for thoses systems
QMAKE_CXXFLAGS  += -isystemlib/bullet/src
QMAKE_CXXFLAGS  += -isystemlib/qwt/src

LIBS += -L../src/lib/bullet/lib

LIBS += -lBulletDynamics
LIBS += -lBulletCollision
LIBS += -lLinearMath
LIBS += -lqwt

SOURCES += \
    genecraft/core/engines/engine.cpp \
    genecraft/core/engines/entities/entitiesengine.cpp \
    genecraft/core/entities/entity.cpp \
    genecraft/core/entities/body/treeshape.cpp \
    genecraft/core/entities/body/fixation.cpp \
    genecraft/core/entities/body/bone.cpp \
    genecraft/core/entities/brain/synapse.cpp \
    genecraft/core/entities/brain/sinusin.cpp \
    genecraft/core/entities/brain/brainpluggrid.cpp \
    genecraft/core/entities/brain/brainnode.cpp \
    genecraft/core/entities/brain/brain.cpp \
    genecraft/core/entities/brain/brainfunctional.cpp \
    genecraft/core/entities/brain/brainin.cpp \
    genecraft/core/entities/brain/brainout.cpp \
    genecraft/core/entities/sensors/sensor.cpp \
    genecraft/core/entities/sensors/positionsensor.cpp \
    genecraft/core/entities/sensors/gyroscopicsensor.cpp \
    genecraft/core/entities/sensors/accelerometersensor.cpp \
    genecraft/core/entities/sensors/smellsensor.cpp \
    genecraft/core/entities/sensors/boxsmellsensor.cpp \
    genecraft/core/entities/sensors/distancesensor.cpp \
    genecraft/core/entities/sensors/contactsensor.cpp \
    genecraft/core/entities/effectors/effector.cpp \
    genecraft/core/entities/effectors/rotationalmotorseffector.cpp \
    genecraft/core/entities/effectors/grippereffector.cpp \
    genecraft/core/entities/effectors/flyingeffector.cpp \
    genecraft/core/entities/entityfamily.cpp \
    genecraft/core/entities/families/genericfamily.cpp \
    genecraft/core/entities/families/spiderfamily.cpp \
    genecraft/core/entities/families/antfamily.cpp \
    genecraft/core/entities/families/caterpillarfamily.cpp \
    genecraft/core/entities/families/snakefamily.cpp \
    genecraft/core/entities/mutation/mutationsmanager.cpp \
    genecraft/core/entities/mutation/mutation.cpp \
    genecraft/core/entities/mutation/floatmutation.cpp \
    genecraft/core/entities/mutation/brainnodemutation.cpp \
    genecraft/core/entities/mutation/integermutation.cpp \
    genecraft/core/entities/mutation/bonelimitsmutation.cpp \
    genecraft/core/entities/mutation/simpleprobabilitymutation.cpp \
    genecraft/core/entities/mutation/structuralmutation.cpp \
    genecraft/core/entities/mutation/structurallist.cpp \
    genecraft/core/entities/mutation/crossovermanager.cpp \
    genecraft/core/entities/statistics/statisticsstorage.cpp \
    genecraft/core/entities/statistics/treeshapestats.cpp \
    genecraft/core/entities/statistics/statisticsprovider.cpp \
    genecraft/core/entities/statistics/fixationstats.cpp \
    genecraft/core/world/spawn.cpp \
    genecraft/core/factories/ressources/jsonfile.cpp \
    genecraft/core/factories/ressources/dbrecord.cpp \
    genecraft/core/factories/ressources/ressourcesmanager.cpp \
    genecraft/core/factories/ressources/ressource.cpp \
    genecraft/core/factories/base/creaturefactory.cpp \
    genecraft/core/experiment/result.cpp \
    genecraft/core/experiment/experimentmanager.cpp \
    genecraft/core/experiment/experiment.cpp \
    genecraft/core/experiment/resultsmanager.cpp \
    genecraft/core/utils/tools.cpp \
    genecraft/core/engines/terrain/terrain.cpp \
    genecraft/core/entities/effectors/brainoutmotor.cpp

HEADERS += \
    genecraft/core/engines/engine.h \
    genecraft/core/engines/entities/entitiesengine.h \
    genecraft/core/entities/entity.h \
    genecraft/core/entities/body/treeshape.h \
    genecraft/core/entities/body/bone.h \
    genecraft/core/entities/body/fixation.h \
    genecraft/core/entities/brain/synapse.h \
    genecraft/core/entities/brain/sinusin.h \
    genecraft/core/entities/brain/brainpluggrid.h \
    genecraft/core/entities/brain/brainnode.h \
    genecraft/core/entities/brain/brain.h \
    genecraft/core/entities/brain/brainfunctional.h \
    genecraft/core/entities/brain/brainin.h \
    genecraft/core/entities/brain/brainout.h \
    genecraft/core/entities/sensors/sensor.h \
    genecraft/core/entities/sensors/positionsensor.h \
    genecraft/core/entities/sensors/gyroscopicsensor.h \
    genecraft/core/entities/sensors/accelerometersensor.h \
    genecraft/core/entities/sensors/contactsensor.h \
    genecraft/core/entities/sensors/smellsensor.h \
    genecraft/core/entities/sensors/boxsmellsensor.h \
    genecraft/core/entities/sensors/distancesensor.h \
    genecraft/core/entities/effectors/effector.h \
    genecraft/core/entities/effectors/rotationalmotorseffector.h \
    genecraft/core/entities/effectors/grippereffector.h \
    genecraft/core/entities/effectors/flyingeffector.h \
    genecraft/core/entities/entityfamily.h \
    genecraft/core/entities/families/snakefamily.h \
    genecraft/core/entities/families/spiderfamily.h \
    genecraft/core/entities/families/antfamily.h \
    genecraft/core/entities/families/caterpillarfamily.h \
    genecraft/core/entities/families/genericfamily.h \
    genecraft/core/entities/statistics/statisticsstorage.h \
    genecraft/core/entities/statistics/treeshapestats.h \
    genecraft/core/entities/statistics/statisticsprovider.h \
    genecraft/core/entities/statistics/fixationstats.h \
    genecraft/core/entities/mutation/mutationsmanager.h \
    genecraft/core/entities/mutation/mutation.h \
    genecraft/core/entities/mutation/floatmutation.h \
    genecraft/core/entities/mutation/brainnodemutation.h \
    genecraft/core/entities/mutation/integermutation.h \
    genecraft/core/entities/mutation/simpleprobabilitymutation.h \
    genecraft/core/entities/mutation/structuralmutation.h \
    genecraft/core/entities/mutation/structurallist.h \
    genecraft/core/entities/mutation/crossovermanager.h \
    genecraft/core/entities/mutation/bonelimitsmutation.h \
    genecraft/core/factories/ressources/ressource.h \
    genecraft/core/factories/ressources/jsonfile.h \
    genecraft/core/factories/ressources/dbrecord.h \
    genecraft/core/factories/base/creaturefactory.h \
    genecraft/core/factories/ressources/ressourcesmanager.h \
    genecraft/core/world/spawn.h \
    genecraft/core/experiment/result.h \
    genecraft/core/experiment/experimentmanager.h \
    genecraft/core/experiment/experiment.h \
    genecraft/core/experiment/resultsmanager.h \
    genecraft/core/utils/tools.h \
    genecraft/core/engines/terrain/terrain.h \
    genecraft/core/entities/effectors/brainoutmotor.h

RESOURCES += \
    genecraft/core/ressources/core.qrc


