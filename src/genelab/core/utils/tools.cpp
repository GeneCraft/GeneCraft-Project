#include "tools.h"
#include <ctime>
#include <cstdlib>

namespace GeneLabCore {

    Tools::Tools() {
        qsrand((unsigned int)time(NULL));
    }

    int Tools::random(int min, int max) {
        //return (int)((max - min) * qrand()/(btScalar) RAND_MAX + min);
        //return min+int((max-min)*(btScalar)qrand()/(RAND_MAX));
        return min + (qrand() % (int)(max - min + 1));
    }

    btScalar Tools::random(btScalar min, btScalar max) {
        return ((max - min) * ((btScalar) qrand()/RAND_MAX)) + min;
    }

//    double Tools::random(double min, double max) {
//        return ((max - min) * ((double) qrand()/RAND_MAX)) + min;
//    }

    // Used to clear a QTreeWidget
    void Tools::clearTreeWidget(QTreeWidget * tree)
    {
        for(int i = 0; i < tree->topLevelItemCount(); i++) {
            delete tree->topLevelItem(i);
        }

        tree->clear();
    }

}
