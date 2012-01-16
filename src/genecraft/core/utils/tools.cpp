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

#include "tools.h"
#include <ctime>
#include <cstdlib>
#include <QDir>
#include <QDebug>

namespace GeneCraftCore {

    Tools::Tools() {
        qsrand((unsigned int)time(NULL));
    }

    int Tools::random(int min, int max) {
        //return (int)((max - min) * qrand()/(btScalar) RAND_MAX + min);
        //return min+int((max-min)*(btScalar)qrand()/(RAND_MAX));
        return min + (qrand() % (int)(max - min + 1));
    }

    //btScalar Tools::random(btScalar min, btScalar max) {
    //    return ((max - min) * ((btScalar) qrand()/RAND_MAX)) + min;
    //}
//#ifndef BT_USE_DOUBLE_PRECISION
    double Tools::random(double min, double max) {
        return ((max - min) * ((double) qrand()/RAND_MAX)) + min;
    }

    /******************************************************************************/

    double Tools::normalRandom(double mu, double sigma) {
            static bool deviateAvailable=false;	//	flag
            static double storedDeviate;			//	deviate from previous calculation
            double dist, angle;

            //	If no deviate has been stored, the standard Box-Muller transformation is
            //	performed, producing two independent normally-distributed random
            //	deviates.  One is stored for the next round, and one is returned.
            if (!deviateAvailable) {

                    //	choose a pair of uniformly distributed deviates, one for the
                    //	distance and one for the angle, and perform transformations
                    dist=sqrt( -2.0 * log(double(rand()) / double(RAND_MAX)) );
                    angle=2.0 * M_PI * (double(rand()) / double(RAND_MAX));

                    //	calculate and store first deviate and set flag
                    storedDeviate=dist*cos(angle);
                    deviateAvailable=true;

                    //	calcaulate return second deviate
                    return dist * sin(angle) * sigma + mu;
            }

            //	If a deviate is available from a previous call to this function, it is
            //	returned, and the flag is set to false.
            else {
                    deviateAvailable=false;
                    return storedDeviate*sigma + mu;
            }
    }
//#endif

    /*btScalar Tools::normalRandom(btScalar mu, btScalar sigma) {
            static bool deviateAvailable=false;	//	flag
            static btScalar storedDeviate;       //	deviate from previous calculation
            btScalar dist, angle;

            //	If no deviate has been stored, the standard Box-Muller transformation is
            //	performed, producing two independent normally-distributed random
            //	deviates.  One is stored for the next round, and one is returned.
            if (!deviateAvailable) {

                    //	choose a pair of uniformly distributed deviates, one for the
                    //	distance and one for the angle, and perform transformations
                    dist=sqrt( -2.0 * log(double(rand()) / double(RAND_MAX)) );
                    angle=2.0 * M_PI * (double(rand()) / double(RAND_MAX));

                    //	calculate and store first deviate and set flag
                    storedDeviate=dist*cos(angle);
                    deviateAvailable=true;

                    //	calcaulate return second deviate
                    return dist * sin(angle) * sigma + mu;
            }

            //	If a deviate is available from a previous call to this function, it is
            //	returned, and the flag is set to false.
            else {
                    deviateAvailable=false;
                    return storedDeviate*sigma + mu;
            }
    }*/


    bool Tools::removeDir(QString dirPath)
    {
        QDir folder(dirPath);
        folder.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
        foreach(QFileInfo fileInfo, folder.entryInfoList())
        {

            if(fileInfo.isDir())
            {
                qDebug() << "- subdir" << fileInfo.filePath();

                if(!removeDir(fileInfo.filePath()))
                    return false;
            }
            else if(fileInfo.isFile())
            {
                qDebug() << "- subfile" << fileInfo.filePath();

                if(!QFile::remove(fileInfo.filePath()))
                {
                    qDebug() << "Unable to remove file : " << fileInfo.filePath();
                    return false;
                }
            }
        }

        if(!folder.rmdir(dirPath))
        {
            qDebug() << "Unable to remove folder : " << dirPath << ". Maybe this folder is not empty";
            return false;
        }

        return true;
    }

/******************************************************************************/
 /* FROM http://www.dreamincode.net/code/snippet1446.htm */
/* randn()
 *
 * Normally (Gaussian) distributed random numbers, using the Box-Muller
 * transformation.  This transformation takes two uniformly distributed deviates
 * within the unit circle, and transforms them into two independently
 * distributed normal deviates.  Utilizes the internal rand() function; this can
 * easily be changed to use a better and faster RNG.
 *
 * The parameters passed to the function are the mean and standard deviation of
 * the desired distribution.  The default values used, when no arguments are
 * passed, are 0 and 1 - the standard normal distribution.
 *
 *
 * Two functions are provided:
 *
 * The first uses the so-called polar version of the B-M transformation, using
 * multiple calls to a uniform RNG to ensure the initial deviates are within the
 * unit circle.  This avoids making any costly trigonometric function calls.
 *
 * The second makes only a single set of calls to the RNG, and calculates a
 * position within the unit circle with two trigonometric function calls.
 *
 * The polar version is generally superior in terms of speed; however, on some
 * systems, the optimization of the math libraries may result in better
 * performance of the second.  Try it out on the target system to see which
 * works best for you.  On my test machine (Athlon 3800+), the non-trig version
 * runs at about 3x10^6 calls/s; while the trig version runs at about
 * 1.8x10^6 calls/s (-O2 optimization).
 *
 *
 * Example calls:
 * randn_notrig();	//returns normal deviate with mean=0.0, std. deviation=1.0
 * randn_notrig(5.2,3.0);	//returns deviate with mean=5.2, std. deviation=3.0
 *
 *
 * Dependencies - requires <cmath> for the sqrt(), sin(), and cos() calls, and a
 * #defined value for PI.
 */

/******************************************************************************/
//	"Polar" version without trigonometric calls
    /*
double randn_notrig(double mu=0.0, double sigma=1.0) {
        static bool deviateAvailable=false;	//	flag
        static float storedDeviate;			//	deviate from previous calculation
        double polar, rsquared, var1, var2;

        //	If no deviate has been stored, the polar Box-Muller transformation is
        //	performed, producing two independent normally-distributed random
        //	deviates.  One is stored for the next round, and one is returned.
        if (!deviateAvailable) {

                //	choose pairs of uniformly distributed deviates, discarding those
                //	that don't fall within the unit circle
                do {
                        var1=2.0*( double(rand())/double(RAND_MAX) ) - 1.0;
                        var2=2.0*( double(rand())/double(RAND_MAX) ) - 1.0;
                        rsquared=var1*var1+var2*var2;
                } while ( rsquared>=1.0 || rsquared == 0.0);

                //	calculate polar tranformation for each deviate
                polar=sqrt(-2.0*log(rsquared)/rsquared);

                //	store first deviate and set flag
                storedDeviate=var1*polar;
                deviateAvailable=true;

                //	return second deviate
                return var2*polar*sigma + mu;
        }

        //	If a deviate is available from a previous call to this function, it is
        //	returned, and the flag is set to false.
        else {
                deviateAvailable=false;
                return storedDeviate*sigma + mu;
        }
}
*/

/******************************************************************************/
/*
//	Standard version with trigonometric calls
#define PI 3.14159265358979323846

double randn_trig(double mu=0.0, double sigma=1.0) {
        static bool deviateAvailable=false;	//	flag
        static float storedDeviate;			//	deviate from previous calculation
        double dist, angle;

        //	If no deviate has been stored, the standard Box-Muller transformation is
        //	performed, producing two independent normally-distributed random
        //	deviates.  One is stored for the next round, and one is returned.
        if (!deviateAvailable) {

                //	choose a pair of uniformly distributed deviates, one for the
                //	distance and one for the angle, and perform transformations
                dist=sqrt( -2.0 * log(double(rand()) / double(RAND_MAX)) );
                angle=2.0 * PI * (double(rand()) / double(RAND_MAX));

                //	calculate and store first deviate and set flag
                storedDeviate=dist*cos(angle);
                deviateAvailable=true;

                //	calcaulate return second deviate
                return dist * sin(angle) * sigma + mu;
        }

        //	If a deviate is available from a previous call to this function, it is
        //	returned, and the flag is set to false.
        else {
                deviateAvailable=false;
                return storedDeviate*sigma + mu;
        }
}*/
}
