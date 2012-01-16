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

#ifndef __CPU_PLOT_H_
#define __CPU_PLOT_H_
#include "qwt_plot.h"
#include <QList>
#include <QScriptEngine>
#include "genecraftcoreclasses.h"
#define HISTORY 1200
#define NB_STAT 14

class QwtPlotCurve;
class QwtPlotMarker;

namespace GeneCraftCore {
    class FitnessPlot : public QwtPlot
    {
        Q_OBJECT
    public:

        FitnessPlot( QWidget * = 0 );
        const QwtPlotCurve *fitnessCurve( int id ) const
        {
            return curves[id].curve;
        }

        void step();
        void reset();
    public slots:
        void setEntity(Entity* e);
        void entityDeleted(Entity* e);
        void setExperiment(Experiment* e);

    private Q_SLOTS:
        void showCurve( QwtPlotItem *, bool on );

    private:
        struct
        {
            QwtPlotCurve *curve;
            double data[HISTORY];
        } curves[NB_STAT];

        double axisData[HISTORY];
        int dataCount;
        int displayedSec;
        int nbData;
        int lastStep;
        int minAge, maxAge;
        Entity* ent;
        Experiment* exp;
        bool ended, broke, die;
        QList<QwtPlotMarker*> markers;
        QList<QString> ignoreStats;


        // Scripting
        QScriptEngine scriptEngine;
        QScriptValue  entityObj;
        QScriptValue  validityFunc;
        QScriptValue  endFunc;
        QScriptValue  dieFunc;
        QScriptValue  fitnessFunc;

    };
}
#endif
