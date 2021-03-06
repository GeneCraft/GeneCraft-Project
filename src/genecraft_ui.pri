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
    genecraft/core/ui \
    genecraft/core/utils

unix {
    INCLUDEPATH += /usr/include/qwt
}

SOURCES += \
    genecraft/core/ui/widgets/entities/brainpropertiescontroller.cpp \
    genecraft/core/ui/widgets/entities/statisticspropertiescontroller.cpp \
    genecraft/core/ui/widgets/entities/fixationpropertiescontroller.cpp \
    genecraft/core/ui/widgets/experiments/experimentspropertiescontroller.cpp \
    genecraft/core/ui/widgets/experiments/floatmutationcontroller.cpp \
    genecraft/core/ui/widgets/experiments/integermutationcontroller.cpp \
    genecraft/core/ui/widgets/experiments/simpleprobabilitycontroller.cpp \
    genecraft/core/ui/widgets/experiments/structuralmutationcontroller.cpp \
    genecraft/core/ui/widgets/experiments/mutationelementcontroller.cpp \
    genecraft/core/ui/widgets/experiments/workerctrl.cpp \
    genecraft/core/ui/widgets/experiments/ressourcesbrowser.cpp \
    genecraft/core/ui/widgets/experiments/experimentctrl.cpp \
    genecraft/core/ui/widgets/entities/generic6dofconstraintcontroller.cpp \
    genecraft/core/ui/widgets/entities/bonepropertiescontroller.cpp \
    genecraft/core/ui/widgets/entities/pluggridvisualizer.cpp \
    genecraft/core/ui/widgets/entities/entitypropertiescontroller.cpp \
    genecraft/core/ui/widgets/entities/pluggriddesignvisualizer.cpp \
    genecraft/core/ui/widgets/experiments/conversionctrl.cpp \
    genecraft/core/ui/widgets/plot/fitnessplot.cpp \
    genecraft/core/ui/widgets/experiments/floordialog.cpp \
    genecraft/core/utils/uitools.cpp

HEADERS += \
    genecraft/core/ui/widgets/experiments/structuralmutationcontroller.h \
    genecraft/core/ui/widgets/experiments/mutationelementcontroller.h \
    genecraft/core/ui/widgets/experiments/workerctrl.h \
    genecraft/core/ui/widgets/experiments/ressourcesbrowser.h \
    genecraft/core/ui/widgets/experiments/ressourcesItems.h \
    genecraft/core/ui/widgets/experiments/experimentctrl.h \
    genecraft/core/ui/widgets/experiments/experimentspropertiescontroller.h \
    genecraft/core/ui/widgets/experiments/floatmutationcontroller.h \
    genecraft/core/ui/widgets/experiments/integermutationcontroller.h \
    genecraft/core/ui/widgets/experiments/simpleprobabilitycontroller.h \
    genecraft/core/ui/widgets/entities/brainpropertiescontroller.h \
    genecraft/core/ui/widgets/entities/statisticspropertiescontroller.h \
    genecraft/core/ui/widgets/entities/fixationpropertiescontroller.h \
    genecraft/core/ui/widgets/entities/pluggriddesignvisualizer.h \
    genecraft/core/ui/widgets/entities/bodyitems.h \
    genecraft/core/ui/widgets/entities/entitypropertiescontroller.h \
    genecraft/core/ui/widgets/entities/pluggridvisualizer.h \
    genecraft/core/ui/widgets/entities/bonepropertiescontroller.h \
    genecraft/core/ui/widgets/entities/generic6dofconstraintcontroller.h \
    genecraft/core/ui/widgets/experiments/conversionctrl.h \
    genecraft/core/ui/widgets/plot/fitnessplot.h \
    genecraft/core/ui/widgets/experiments/floordialog.h \
    genecraft/core/utils/uitools.h

FORMS += \
    genecraft/core/ui/widgets/entities/generic6dofconstraintcontroller.ui \
    genecraft/core/ui/widgets/entities/bonepropertiescontroller.ui \
    genecraft/core/ui/widgets/entities/entitypropertiescontroller.ui \
    genecraft/core/ui/widgets/entities/brainpropertiescontroller.ui \
    genecraft/core/ui/widgets/entities/statisticspropertiescontroller.ui \
    genecraft/core/ui/widgets/entities/fixationpropertiescontroller.ui \
    genecraft/core/ui/widgets/experiments/experimentspropertiescontroller.ui \
    genecraft/core/ui/widgets/experiments/floatmutationcontroller.ui \
    genecraft/core/ui/widgets/experiments/integermutationcontroller.ui \
    genecraft/core/ui/widgets/experiments/simpleprobabilitycontroller.ui \
    genecraft/core/ui/widgets/experiments/structuralmutationcontroller.ui \
    genecraft/core/ui/widgets/experiments/mutationelementcontroller.ui \
    genecraft/core/ui/widgets/experiments/workerctrl.ui \
    genecraft/core/ui/widgets/experiments/ressourcesbrowser.ui \
    genecraft/core/ui/widgets/experiments/experimentctrl.ui \
    genecraft/core/ui/widgets/experiments/conversionctrl.ui \
    genecraft/core/ui/widgets/experiments/floordialog.ui

RESOURCES += \
    genecraft/core/ressources/ressources.qrc
