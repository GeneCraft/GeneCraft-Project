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

#include <qapplication.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qpainter.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_widget.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_marker.h>
#include "fitnessplot.h"
#include <QTime>
#include <QDebug>
#include "entity.h"
#include "experiment.h"
#include <QScriptValue>
#include <QScriptEngine>


namespace GeneCraftCore {
    class StepScaleDraw: public ::QwtScaleDraw
    {
    public:
        StepScaleDraw( const QTime &base ):
            baseTime( base ), step(base.hour()*3600*60 + base.minute()*3600 + base.second()*60)
        {
        }

        virtual QwtText label( double v ) const
        {
            QTime upTime = baseTime.addSecs( static_cast<int>( v/60. ) );
            int actStep = step + (int)v;
            return upTime.toString() + "\n(" + QString::number(actStep)+ " steps)";
        }
    private:
        QTime baseTime;
        int step;
    };

    class Background: public ::QwtPlotItem
    {
    public:
        Background()
        {
            setZ( 0.0 );
        }

        virtual int rtti() const
        {
            return QwtPlotItem::Rtti_PlotUserItem;
        }

        virtual void draw( QPainter *painter,
            const QwtScaleMap &, const QwtScaleMap &,
            const QRectF &canvasRect ) const
        {
            QColor c( Qt::white );
            QRectF r = canvasRect;

            for ( int i = 0; i < canvasRect.height(); i += canvasRect.height()/10. )
            {
                r.setBottom( i );
                r.setTop( i + canvasRect.height()/10.  );
                painter->fillRect(r, c);


                c = c.dark( 110 );
            }
        }
    };

    class FitnessCurve: public ::QwtPlotCurve
    {
    public:
        FitnessCurve( const QString &title ):
            QwtPlotCurve( title )
        {
            setRenderHint( QwtPlotItem::RenderAntialiased );
        }

        void setColor( const QColor &color )
        {
            QPen p;
            QColor c = color;
            c.setAlpha( 150 );

            p.setColor(c);
            p.setWidthF(2.);
            //p.setStyle(Qt::DotLine);
            setPen(p);
            setBrush( c );
        }
    };

    FitnessPlot::FitnessPlot( QWidget *parent ):
        QwtPlot( parent ),
        dataCount( 0 ), lastStep(0), ent(NULL), exp(NULL)
    {
        this->ignoreStats.append("bodyBones");
        this->ignoreStats.append("bodySensors");
        this->ignoreStats.append("bodyEffectors");
        this->ignoreStats.append("bodyWeight");
        this->ignoreStats.append("bodyLength");
        this->ignoreStats.append("age");
        this->ignoreStats.append("brainActivity");

        setAutoReplot( false );

        canvas()->setBorderRadius( 10 );

        plotLayout()->setAlignCanvasToScales( true );

        QwtLegend *legend = new QwtLegend;
        legend->setItemMode( QwtLegend::CheckableItem );
        insertLegend( legend, QwtPlot::RightLegend );

        /*
         In situations, when there is a label at the most right position of the
         scale, additional space is needed to display the overlapping part
         of the label would be taken by reducing the width of scale and canvas.
         To avoid this "jumping canvas" effect, we add a permanent margin.
         We don't need to do the same for the left border, because there
         is enough space for the overlapping label below the left scale.
         */

        QwtScaleWidget *scaleWidget = axisWidget( QwtPlot::xBottom );
        const int fmh = QFontMetrics( scaleWidget->font() ).height();
        scaleWidget->setMinBorderDist( 0, fmh / 2 );

        setAxisTitle( QwtPlot::yLeft, "Actual fitness [%]" );
        Background *bg = new Background();
        bg->attach( this );

        FitnessCurve *curve;

        curve = new FitnessCurve( "Result" );
        curve->setColor( Qt::green );
        curve->attach( this );

        curves[0].curve = curve;
        for(int i = 1; i< NB_STAT; i++) {
            curves[i].curve = NULL;
        }

        connect( this, SIGNAL( legendChecked( QwtPlotItem *, bool ) ),
            SLOT( showCurve( QwtPlotItem *, bool ) ) );

        this->reset();
    }

    void FitnessPlot::step()
    {

        if(!ent)
            return;

        if(!exp)
            return;

        int age = ent->getAge();

        if(age == 0)
            reset();

        if(age == lastStep)
            return;

        lastStep = age;

        QScriptValue fitnessVal = fitnessFunc.call();
        float fitness = fitnessVal.toNumber();
        if(isinf(fitness) || isnan(fitness)) {
            fitness = 0;
        }

        QScriptValue endBool = endFunc.call(QScriptValue(), QScriptValueList() << age);
        bool end = endBool.toBool();
        if(end && !ended) {
            ended = true;
            QwtPlotMarker* m = new QwtPlotMarker();
            m->setYValue(fitness);
            m->setXValue(age);
            m->setVisible(true);
            m->setLinePen(QPen(Qt::blue));
            m->setLineStyle(QwtPlotMarker::VLine);
            m->attach(this);
            m->setLabel("End (user) fitness = " + QString::number(fitness));
            markers << m;
        }

        if(age == exp->getDuration()) {
            QwtPlotMarker* m = new QwtPlotMarker();
            m->setYValue(fitness);
            m->setXValue(age);
            m->setVisible(true);
            m->setLinePen(QPen(Qt::black));
            m->setLineStyle(QwtPlotMarker::VLine);
            m->attach(this);
            m->setLabel("End (duration) fitness = " + QString::number(fitness));
            markers << m;
        }

        if(!ent->isAlive() && !broke) {
            broke = true;
            QwtPlotMarker* m = new QwtPlotMarker();
            m->setYValue(fitness);
            m->setXValue(age);
            m->setVisible(true);
            m->setLinePen(QPen(Qt::yellow));
            m->setLineStyle(QwtPlotMarker::VLine);
            m->attach(this);
            m->setLabel("Dead (expl.) fitness = " + QString::number(fitness));
            markers << m;
        }

        QScriptValue dead = dieFunc.call();
        bool isDead = dead.toBool();
        if(isDead && !die) {
            die = true;
            QwtPlotMarker* m = new QwtPlotMarker();
            m->setYValue(fitness);
            m->setXValue(age);
            m->setVisible(true);
            m->setLinePen(QPen(Qt::red));
            m->setLineStyle(QwtPlotMarker::VLine);
            m->attach(this);
            m->setLabel("Dead (user) fitness = " + QString::number(fitness));
            markers << m;
        }


        float min = 0;
        float max = 100;
        for(int i = 0; i < NB_STAT; i++) {
            if(curves[i].curve == NULL)
                break;

            FitnessCurve* c = (FitnessCurve*)curves[i].curve;
            if(c->isVisible()) {

                min = curves[i].data[0];
                max = curves[i].data[0];
                break;
            }
        }
        if(isnan(min) || isinf(min))
            min = 0;

        if(isnan(max) || isinf(max))
            max = 0;

        for(int i = 0; i < NB_STAT; i++) {

            if(curves[i].curve == NULL)
                break;

            for ( int j = dataCount; j > 0; j-- )
            {
                if ( j == HISTORY )
                    continue;

                FitnessCurve* c = (FitnessCurve*)curves[i].curve;
                if(c->isVisible()) {
                    if(min > curves[i].data[j] && !isnan(curves[i].data[j]) && !isinf(curves[i].data[j])) {
                        min = curves[i].data[j];
                    }

                    if(max < curves[i].data[j] && !isnan(curves[i].data[j]) && !isinf(curves[i].data[j])) {
                        max = curves[i].data[j];
                    }
                }

                curves[i].data[j] = curves[i].data[j-1];
            }
        }


        for ( int j = dataCount; j > 0; j-- )
        {
            if ( j == HISTORY )
                continue;
            axisData[j] = axisData[j-1];
        }


        curves[0].data[0] = fitness;
        axisData[0] = age;


        int i = 0;
        foreach(QString s, ent->getStatisticsStorage()->getStatistics().keys()) {
            if(ignoreStats.contains(s))
                continue;

            i++;
            if(i == NB_STAT || curves[i].curve == NULL)
                break;

            curves[i].data[0] = ent->getStatisticsStorage()->getStatistics()[s]->getValue();
            if(isnan(curves[i].data[0]) || isinf(curves[i].data[0]))
                curves[i].data[0] = 0;

        }

        min -= qAbs(min) * 0.1;
        max += qAbs(max) * 0.1;


        if ( dataCount < HISTORY ) {
            dataCount++;
        }

        int nbSteps = 30;

        minAge = qMax(((int)(axisData[0] - 1200)/nbSteps + 1)*nbSteps, minAge);

        if(maxAge < (int)HISTORY*nbSteps/nbSteps + (int)axisData[dataCount -1]) {
            maxAge += nbSteps*6;
        }


          // (int)(qMax(axisData[0] - interval*HISTORY/nbSteps, (double)minAge))/interval*interval + interval,
        //(int)(axisData[0])/interval*interval + interval, interval);


        static int cpt = 0;
        cpt++;
        if(cpt%10 == 0) {

            setAxisScale( QwtPlot::yLeft, min, max );
            setAxisScale(QwtPlot::xBottom, minAge, maxAge, nbSteps*4);

            for(int i = 0; i < NB_STAT; i++) {
                if(curves[i].curve)
                curves[i].curve->setRawSamples(
                    axisData, curves[i].data, HISTORY );
            }

            replot();
        }
    }

    void FitnessPlot::showCurve( QwtPlotItem *item, bool on )
    {
        item->setVisible( on );

        QwtLegendItem *legendItem =
            qobject_cast<QwtLegendItem *>( legend()->find( item ) );

        if ( legendItem )
            legendItem->setChecked( on );

        replot();
    }

    void FitnessPlot::reset() {

        qDebug() << "reset plot ";

        ended = false;
        broke = false;
        die = false;
        minAge = 0;
        maxAge = 0;
        dataCount = 0;
        lastStep = 0;

        foreach(QwtPlotMarker* m, markers) {
            m->detach();
            delete m;
        }

        markers.clear();

        setAxisTitle( QwtPlot::xBottom, " Simulation time [h:m:s]" );
        setAxisScaleDraw( QwtPlot::xBottom,
                          new StepScaleDraw(QTime()) );
        setAxisScale( QwtPlot::xBottom, 0, HISTORY );
        //setAxisLabelRotation( QwtPlot::xBottom, -50.0 );
        //setAxisLabelAlignment( QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom );


        setAxisScale( QwtPlot::yLeft, 0, 100 );


        if(ent) {
            int i = 0;
            foreach(QString s, ent->getStatisticsStorage()->getStatistics().keys()) {
                if(ignoreStats.contains(s))
                    continue;

                i++;
                if(i == NB_STAT)
                    break;

                FitnessCurve *curve;

                curve = new FitnessCurve( s );
                curve->setColor( QColor(i*255/NB_STAT, 0, 255 - i*255/NB_STAT) );
                curve->setBrush(Qt::NoBrush);
                curve->attach( this );

                bool visible = false;
                if(curves[i].curve) {
                    FitnessCurve* curve = (FitnessCurve*)curves[i].curve;
                    curve->detach();
                    visible = curve->isVisible();
                    delete curves[i].curve;
                    curves[i].curve = NULL;
                }

                curves[i].curve = curve;

                showCurve( curves[i].curve, visible );
            }
        } else {

            /*for(int i = 1; i < NB_STAT; i++) {
                if(curves[i].curve) {
                    FitnessCurve* curve = (FitnessCurve*)curves[i].curve;
                    curve->detach();
                    delete curves[i].curve;
                    curves[i].curve = NULL;
                }
            }*/
        }

        showCurve( curves[0].curve, true );

        for(int j = 0; j < NB_STAT; j++) {
            for ( int i = 0; i < HISTORY; i++ ) {
                axisData[HISTORY - 1 - i] = 0;
                curves[j].data[i] = 0;
            }
        }


    }

    void FitnessPlot::setEntity(Entity *e) {
        qDebug() << "ent" << e;
        if(e) {
            if(e == ent)
                return;

            this->ent = e;

            // Create a new empty script object
            entityObj      = scriptEngine.newObject();

            // For each statistics of the entity
            QMap<QString, Statistic*> stats = e->getStatisticsStorage()->getStatistics();
            foreach(QString statName, stats.keys()) {
                Statistic* stat = stats[statName];
                // Insert a new properties of our top level object
                // With the name of the statistic
                QScriptValue statObject = scriptEngine.newQObject(stat);
                entityObj.setProperty(statName, statObject);
            }

            // And set the new object created as the "entity" object
            // in the global scope
            scriptEngine.globalObject().setProperty("entity", entityObj);
        }
        else
            this->ent = NULL;

        reset();
    }

    void FitnessPlot::setExperiment(Experiment *e) {
        qDebug() << "exp" << e;
        if(e) {
            if(exp == e)
                return;

            this->exp = e;


            fitnessFunc  = scriptEngine.evaluate(exp->getEvalFunction());
            validityFunc = scriptEngine.evaluate(exp->getValidityFunction());
            endFunc      = scriptEngine.evaluate(exp->getEndFunction());
            dieFunc      = scriptEngine.evaluate(exp->getDieFunction());
        }
        else {
            this->exp = NULL;
            this->ent = NULL;
        }

        this->reset();
    }

    void FitnessPlot::entityDeleted(Entity *e) {
        if(e == ent) {
            ent = NULL;
            reset();
        }
    }
}
