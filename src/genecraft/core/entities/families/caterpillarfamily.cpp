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

#include "caterpillarfamily.h"

#include "body/treeshape.h"
#include "body/fixation.h"
#include "body/bone.h"
#include <QVariant>
#include <cmath>
#include "tools.h"
#include "sensors/accelerometersensor.h"
#include "sensors/positionsensor.h"
#include "sensors/gyroscopicsensor.h"
#include "sensors/contactsensor.h"
#include "btshapesfactory.h"

namespace GeneCraftCore {

    CaterpillarFamily::CaterpillarFamily(QObject *parent) :
        EntityFamily(parent)
    {
        this->length = Tools::random(2,10);
        this->pieceLength = Tools::random(.3,.6);
        this->pieceRadius = Tools::random(0.3,0.5);
        this->fixRadius = pieceRadius;

        this->legLength = Tools::random(.1,pieceLength * 0.5);
        this->legRadius = Tools::random(.1,pieceRadius * 0.5);

        this->antennaPieces = Tools::random(2,4);
        this->antennaLength = Tools::random(.1,0.2);
        this->antennaRadius = Tools::random(.1,0.1);
    }

    CaterpillarFamily::CaterpillarFamily(QVariant data, QObject *parent) :
        EntityFamily(parent)
    {
        this->length = data.toMap()["length"].toInt();

        this->pieceLength = data.toMap()["piecelength"].toFloat();
        this->pieceRadius = data.toMap()["pieceRadius"].toFloat();
    }

    Entity* CaterpillarFamily::createEntity(btShapesFactory* factory, const btVector3 &position) {

        // create entity
        Entity* entity = new Entity("Yet Another Caterpillar", "Caterpillar","generic", 1);

        // create brain
        entity->setBrain(new BrainFunctional());

        // create root fixation
        btTransform initTransform;
        initTransform.setIdentity();
        initTransform.setOrigin(position);
        Fixation* root = new Fixation(factory,fixRadius,initTransform);
        //Fixation* reelRoot = root;

        // shape
        TreeShape* shape = new TreeShape(factory);
        shape->setRoot(root);
        entity->setShape(shape);

        // liberty angle
        btScalar xAngle = SIMD_PI * 0.06;
        btScalar yAngle = 0;
        btScalar zAngle = SIMD_PI * 0.5;

        Bone* b;

        // build body
        for(int i = 0; i < length; i++) {

            if(i == 0){

                // neck
                b = root->addBone(0., SIMD_PI/2.,
                                  pieceRadius,
                                  pieceLength / 3.f,
                                  fixRadius,
                                  btVector3(0,0,0),
                                  btVector3(0,0,0));
            } else {

                // body piece
                b = root->addBone(0., 0.,
                                  pieceRadius,
                                  pieceLength,
                                  fixRadius,
                                  btVector3(-xAngle,-yAngle,-zAngle),
                                  btVector3(xAngle,yAngle,zAngle));

            }

            //b->getEndFixation()->addSensor(new GyroscopicSensor(b->getEndFixation()));
            //b->getEndFixation()->addSensor(new PositionSensor(shape->getRoot(),b->getEndFixation()));

            root = b->getEndFixation();

            // add legs
            for(int i=-1;i<2;i+=2) {
                b = root->addBone(SIMD_PI / 6 * i, SIMD_PI / 2,
                              legRadius,
                              legLength,
                              legRadius,
                              btVector3(-SIMD_PI / 10,0,-SIMD_PI / 10),
                              btVector3(SIMD_PI / 10,0,SIMD_PI / 10));

                //b->getEndFixation()->addSensor(new GyroscopicSensor(b->getEndFixation()));
                //b->getEndFixation()->addSensor(new PositionSensor(shape->getRoot(),b->getEndFixation()));
                //b->getEndFixation()->addSensor(new ContactSensor(b->getEndFixation()));
            }
        }

        // antennae
        /*for(int i=-1;i<2;i+=2) {
            root = reelRoot;
            for(int j=0; j< antennaPieces; j++) {

                btScalar yAxis, zAxis;

                // first piece of antenna
                if(j == 0){
                    yAxis = SIMD_PI / 2. + SIMD_PI / 8 * i;
                    zAxis = SIMD_PI * 0.7;
                }
                // others
                else{
                    yAxis = SIMD_PI / 8 * i;
                    zAxis = -SIMD_PI * Tools::random(0.1f,0.4f);
                }

                // add new piece
                b = root->addBone(yAxis, zAxis,
                              antennaRadius,
                              antennaLength,
                              antennaRadius,
                              btVector3(0,0,0),
                              btVector3(0,0,0));

                // last piece of antenna
                if(j == antennaPieces-1)
                    b->getEndFixation()->addSensor(new ContactSensor(b->getEndFixation()));

                root = b->getEndFixation();
            }
        }*/
        return entity;
    }

    QVariant CaterpillarFamily::serialize(Entity *entity) {
        QVariantMap data;
        data["length"] = QVariant(length);
        data["piecelength"] = QVariant(pieceLength);
        data["pieceRadius"] = QVariant(pieceRadius);
        return data;
    }
}
