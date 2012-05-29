/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "brainoutmotor.h"
#include <QString>
#include "genecraftcoreclasses.h"
#include "effector.h"
#include "brain/brainout.h"
namespace GeneCraftCore {

    BrainOutMotor::BrainOutMotor(btRotationalLimitMotor * motor,
                  btScalar min_Contraction, btScalar max_Contraction,
                  btScalar min_Expansion, btScalar max_Expansion) : motor(motor)
    {
        boMaxMotorForce = new BrainOut(min_Contraction,max_Contraction);
        boTargetVelocity = new BrainOut(min_Expansion,max_Expansion);
    }

    BrainOutMotor::~BrainOutMotor() {
        delete this->boMaxMotorForce;
        delete this->boTargetVelocity;
    }

    BrainOutMotor::BrainOutMotor(QVariant data, btRotationalLimitMotor* motor) : motor(motor){
        QVariantMap outMap = data.toMap();

        // new version
        if(outMap.contains("contractionOutput")) {
            boMaxMotorForce = new BrainOut(outMap["contractionOutput"]);
            boTargetVelocity = new BrainOut(outMap["expansionOutput"]);
        }
        // old version
        else {
            QVariantList dataL = outMap["brainOuts"].toList();
            boMaxMotorForce = new BrainOut(dataL[0]);
            boTargetVelocity = new BrainOut(dataL[1]);
        }
    }

    QVariant BrainOutMotor::serialize()  {

        QVariantMap data;

        // old version
        // QVariantList outs;
        // outs.append(boMaxMotorForce->serialize());
        // outs.append(boTargetVelocity->serialize());
        // data.insert("brainOuts", (QVariantList)outs);

        // new version
        data.insert("contractionOutput",boMaxMotorForce->serialize());
        data.insert("expansionOutput",boTargetVelocity->serialize());

        return data;
    }

    // To generate an empty version
    QVariant BrainOutMotor::generateEmpty(){

        QVariantMap data;
        BrainOut boContraction(MIN_CONTRACTION,MAX_CONTRACTION);
        BrainOut boExpansion(MIN_EXPANSION,MAX_EXPANSION);
        data.insert("contractionOutput",boContraction.serialize());
        data.insert("expansionOutput",boExpansion.serialize());
        return data;
    }

    void BrainOutMotor::update()
    {
        motor->m_maxMotorForce
                = (boMaxMotorForce->getValue() + boTargetVelocity->getValue())*20000;
        motor->m_targetVelocity
                = (boTargetVelocity->getValue() - boMaxMotorForce->getValue())*20;

        //qDebug() << "Mouvement : " << boMaxMotorForce->getValue() << ", " << boTargetVelocity->getValue();
    }

}
