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

#ifndef INTEGERMUTATION_H
#define INTEGERMUTATION_H

#include "mutation.h"

namespace GeneCraftCore {

    class IntegerMutation : public Mutation {
    public:

        IntegerMutation(QJsonObject variant);
        IntegerMutation();
        QJsonObject serialize();

        void mutate(QJsonObject &map, QString key);
        int mutate(int value);
        int minIncr;
        int maxIncr;
        int minValue;
        int maxValue;
    };

}

#endif // INTEGERMUTATION_H
