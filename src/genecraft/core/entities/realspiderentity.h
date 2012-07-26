/*
Copyright 2011, 2012 David Zéni

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

#ifndef REALSPIDERENTITY_H
#define REALSPIDERENTITY_H

#include "entity.h"
#include <QList>
#include "entities/body/leg.h"

namespace GeneCraftCore {

/**
 * (c) COPYRIGHT GeneCraft 2012, Aurelien Da Campo, Cyprien Huissoud & Zéni David
 *
 * A specific entity for the real spider family .
 *
 * @version 1.0 | May 2011
 * @author Zéni David
 */
class RealSpiderEntity : public Entity
{
public:

    /**
     * @brief Create a realspiderentity
     *
     */
    RealSpiderEntity(QString name, QString family, QString type, int generation, QObject *parent = 0);
    /**
     * @brief Setup the entity
     *
     */
    void setup();
    /**
     * @brief Add a leg to the left
     *
     */
    void addLeftLeg(Leg* leg);
    /**
     * @brief Add a leg to the right
     *
     * @param leg
     *
     */
    void addRightLeg(Leg* leg);
    /**
     * @brief remove a specific left leg
     *
     * @param leg
     *
     */
    void removeLeftLeg(int leg);
    /**
     * @brief remove a specific right leg
     *
     * @param leg
     *
     */
    void removeRightLeg(int leg);
    /**
     * @brief remove all right legs
     *
     */
    void removeAllRightLegs();
    /**
     * @brief remove all left legs
     *
     */
    void removeAllLeftLegs();
    /**
     * @brief remove all legs
     *
     */
    void removeAllLegs();
    /**
     * @brief serialize the real spider entity
     *
     */
    QVariant serialize();
    /**
     * @brief return the real spider parameters
     *
     */
    QVariant getParams();
    /**
     * @brief Set the real spider parameters
     *
     * @param params
     *
     */
    void setParams(QVariant params);
protected:
    QList<Leg*> leftLegs;
    QList<Leg*> rightLegs;
    QVariant parameters;
};
}

#endif // REALSPIDERENTITY_H
