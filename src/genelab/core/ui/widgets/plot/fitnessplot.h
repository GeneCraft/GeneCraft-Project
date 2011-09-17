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
