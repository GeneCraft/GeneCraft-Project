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

#include "snakefamily.h"
#include "body/treeshape.h"
#include "body/fixation.h"
#include "body/bone.h"
#include <QJsonObject>
#include <cmath>
#include "tools.h"
#include "sensors/accelerometersensor.h"
#include "sensors/positionsensor.h"
#include "sensors/gyroscopicsensor.h"

namespace GeneCraftCore {

    SnakeFamily::SnakeFamily(QObject *parent) :
        EntityFamily(parent)
    {
        this->length = Tools::random(5,20);
        this->pieceLength = Tools::random(.1,2.);
        this->pieceRadius = Tools::random(0.1,1.0);
        this->fixRadius = Tools::random(0.1,1.0);
    }

    SnakeFamily::SnakeFamily(QJsonObject data, QObject *parent) :
        EntityFamily(parent)
    {
        this->length = data.toMap()["length"].toInt();

        this->pieceLength = data.toMap()["piecelength"].toFloat();
        this->pieceRadius = data.toMap()["pieceRadius"].toFloat();
    }

    Entity* SnakeFamily::createEntity(btShapesFactory* factory, const btVector3 &position) {

        // create entity
        Entity* entity = new Entity("Snake", "SnakeFamily", "generic", 1);

        // create brain
        entity->setBrain(new BrainFunctional());

        // create root fixation
        btTransform initTransform;
        initTransform.setIdentity();
        initTransform.setOrigin(position);
        Fixation* root = new Fixation(factory,fixRadius,initTransform);

        // shape
        TreeShape* shape = new TreeShape(factory);
        shape->setRoot(root);
        entity->setShape(shape);

        // liberty angle
        btScalar xAngle = SIMD_PI * 0.5;
        btScalar yAngle = 0;
        btScalar zAngle = SIMD_PI * 0.06;

        Bone* b;

        // build body
        for(int i = 0; i < length; i++) {

            if(i == 0){

                // neck
                b = root->addBone(0, SIMD_PI*0.5,
                                  pieceRadius,
                                  pieceLength / 3.f,
                                  fixRadius,
                                  btVector3(0,0,0),
                                  btVector3(0,0,0));
            } else {

                // body piece
                b = root->addBone(0., 0.,
                                  pieceRadius/(1+1.6180339887 * (i) / 10),
                                  pieceLength/(1+1.6180339887 * (i) / 10),
                                  fixRadius/(1+1.6180339887 * (i) / 10),
                                  btVector3(-xAngle,-yAngle,-zAngle),
                                  btVector3(xAngle,yAngle,zAngle));

            }

            root = b->getEndFixation();
        }

//        Entity* snake = new Entity("Snaky"+QString::number(length), "Snake","generic", 1);
//        snake->setBrain(new BrainFunctional());

//        TreeShape* snakeShape = new TreeShape(factory);

//        btTransform initTransform;
//        initTransform.setIdentity();
//        initTransform.setOrigin(position);
//        //initTransform.setRotation(btQuaternion(btVector3(1, 0, 0), SIMD_PI/2.));

//        Fixation* root = new Fixation(factory,fixRadius,initTransform);
//        snakeShape->setRoot(root);
//        snake->setShape(snakeShape);

//        btScalar angle = SIMD_PI - SIMD_PI / 3;

//        // Build body
//        Bone* b = root->addBone(0, SIMD_PI/2., pieceRadius,
//                                pieceLength,
//                                fixRadius,
//                                btVector3(-angle,-SIMD_PI/4,-angle),
//                                btVector3(angle,SIMD_PI/4,angle));

//        root = b->getEndFixation();

//        //b->getEndFixation()->addSensor(new GyroscopicSensor(b->getEndFixation()));

//        for(int i = 0; i < length; i++) {
//            Bone* b = root->addBone(0., 0.,
//                                    pieceRadius/(1+1.6180339887 * (i) / 10),
//                                    pieceLength/(1+1.6180339887 * (i) / 10),
//                                    fixRadius/(1+1.6180339887 * (i) / 10),
//                                    btVector3(-angle,-SIMD_PI/4,-angle),
//                                    btVector3(angle,SIMD_PI/4,angle));

//            //b->getEndFixation()->addSensor(new GyroscopicSensor(b->getEndFixation()));
//            //b->getEndFixation()->addSensor(new PositionSensor(snakeShape->getRoot(),b->getEndFixation()));

//            root = b->getEndFixation();
//        }

        return entity;
    }

    QJsonObject SnakeFamily::serialize() {
        QJsonObject data;
        data["length"] = length;
        data["piecelength"] = pieceLength;
        data["pieceRadius"] = pieceRadius;
        return data;
    }
}
